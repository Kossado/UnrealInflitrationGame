// Fill out your copyright notice in the Description page of Project Settings.


#include "GCCharacter.h"

#include "GCPlayerCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGCCharacter::AGCCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer),
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
void AGCCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Setup overlap for AreaSphere
	if(CollisionMesh)
	{
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AGCCharacter::OnBoxBeginOverlap);
		CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AGCCharacter::OnBoxEndOverlap);
	}
}

// Called every frame
void AGCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Setting up Interact input
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGCCharacter::Interact);
}

void AGCCharacter::CarryFood(AFood* FoodToCarry)
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

void AGCCharacter::ChangeCharacterSpeed(float NewSpeed, float SpeedMultiplicator)
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed * SpeedMultiplicator;
	}
}

void AGCCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(Food && FoodToPick == nullptr)
	{
		FoodToPick = Food;
	}
	AChest* Chest = Cast<AChest>(OtherActor);
	if(Chest)
	{
		ChestInFront = Chest;
	}
	AChair* Chair = Cast<AChair>(OtherActor);
	if(Chair)
	{
		ChairInFront = Chair;
	}
}

void AGCCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(FoodToPick == Food)
	{
		FoodToPick = nullptr;
	}
	AChest* Chest = Cast<AChest>(OtherActor);
	if(Chest == ChestInFront)
	{
		ChestInFront = nullptr;
	}
	AChair* Chair = Cast<AChair>(OtherActor);
	if(Chair == ChairInFront)
	{
		ChairInFront = nullptr;
	}
}

void AGCCharacter::Interact()
{
	// When "E" key is pressed ...
	if(ChairInFront != nullptr && !bIsSitting)
	{
		SitDown();
		return;
	}
	if(bIsSitting)
	{
		StandUp();
		return;
	}
	//... Drop food in hand if not empty handed ...
	if(CarriedFood != nullptr)
	{
		DropFood();
		return;
	}
	if(FoodToPick != nullptr)//... Pick food if there is in front of the character ...
	{
		CarryFood(FoodToPick);
	}
}

void AGCCharacter::SitDown()
{
	if(ChairInFront != nullptr)
	{
		bIsSitting = true;
		ChairInFront->SetCollisionProperties(bIsSitting);
		GetCharacterMovement()->GravityScale = 0.f;
		SetActorLocation(ChairInFront->GetSitLocation());
		SetActorRotation(ChairInFront->GetSitRotation());
	}
}

void AGCCharacter::StandUp()
{
	bIsSitting = false;
	GetCharacterMovement()->GravityScale = 1.f;

	// To Modify => ChairInFront become null when the character sit // BoxCollision should take the character too or change the way of doing it
	if(ChairInFront != nullptr)
	{
		ChairInFront->SetCollisionProperties(bIsSitting);
	}
}

void AGCCharacter::StoreFood()
{
	CarriedFood->SetActorLocation(ChestInFront->GetValidStoredPosition());
	CarriedFood->SetActorRotation(ChestInFront->GetActorRotation() + FRotator(90.f,0.f,0.f));
	LevelGameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(LevelGameMode)
		LevelGameMode->IncrementStoredFood();
}

void AGCCharacter::DropFood()
{
	if(CarriedFood)
	{
		// Detach food from the hand socket
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		CarriedFood->GetFoodMesh()->DetachFromComponent(DetachmentTransformRules);
		// Change food state (Re-enable collisions,...)
		if(ChestInFront)
		{
			CarriedFood->SetFoodState(EFS_Stored);
			StoreFood();
		}
		else
			CarriedFood->SetFoodState(EFoodState::EFS_Dropped);
		CarriedFood = nullptr;
		ChangeCharacterSpeed(BaseWalkSpeed, 1.f);
	}
}

