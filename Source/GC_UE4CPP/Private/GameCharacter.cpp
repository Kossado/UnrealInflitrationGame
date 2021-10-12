// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCharacter::AGameCharacter():
BaseWalkSpeed(300.f),
CarryWalkSpeedMultiplicator(0.5f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetRelativeTransform(FTransform(FVector(0.f,0.f,70.f)));
	CollisionMesh->SetBoxExtent(FVector(32.f,32.f,88.f));
	
	CollisionMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	// Set Maximum movement speed of the character
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Setup overlap for AreaSphere
	if(CollisionMesh)
	{
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AGameCharacter::OnBoxBeginOverlap);
		CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AGameCharacter::OnBoxEndOverlap);
	}
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Setting up Interact input
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGameCharacter::Interact);
}

void AGameCharacter::CarryFood(AFood* FoodToCarry)
{
	if(FoodToCarry)
	{
		FoodToCarry->SetFoodState(EFoodState::EFS_PickedUp);
		//Get the Hand Socket
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("HandSocket"));
		if(HandSocket)
		{
			// Attach food to the hand socket
			HandSocket->AttachActor(FoodToCarry,GetMesh());
		}
		CarriedFood = FoodToCarry;
		ChangeCharacterSpeed(BaseWalkSpeed, CarryWalkSpeedMultiplicator);
	}
}

void AGameCharacter::ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator)
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed * SpeedMultiplicator;
	}
}

void AGameCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(Food && FoodToPick == nullptr)
	{
		FoodToPick = Food;
	}
}

void AGameCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(FoodToPick == Food)
	{
		FoodToPick = nullptr;
	}
}

void AGameCharacter::Interact()
{
	if(FoodToPick != nullptr && CarriedFood == nullptr)
	{
		CarryFood(FoodToPick);
	}else if(FoodToPick == nullptr && CarriedFood != nullptr)
	{
		DropFood();
	}else if(FoodToPick != nullptr && CarriedFood!=nullptr)
	{
		// Swap food with the other one
		DropFood();
		CarryFood(FoodToPick);
	}
	
}

void AGameCharacter::DropFood()
{
	if(CarriedFood)
	{
		// Detach food from the hand socket
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		CarriedFood->GetFoodMesh()->DetachFromComponent(DetachmentTransformRules);
		// Change food state (Re-enable collisions,...)
		CarriedFood->SetFoodState(EFoodState::EFS_Dropped);
		CarriedFood = nullptr;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
		// ONLY FOR TEST PURPOSE - TO DELETE
		//MainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		MainGameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
		if(MainGameMode)
			MainGameMode->IncrementStoredFood();
	}
}
