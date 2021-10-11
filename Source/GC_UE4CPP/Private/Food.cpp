// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Kismet/GameplayStatics.h"

#include "Hero.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	//Set up AreaSphere
	AreaSphere = CreateDefaultSubobject<USphereComponent>(FName(TEXT("AreaSphere")));
	AreaSphere->SetupAttachment(StaticMesh);
	AreaSphere->SetSphereRadius(100.f);
	//Set up food state
	SetFoodState(EFS_Dropped);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	// Setup overlap for AreaSphere
	if(AreaSphere)
	{
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AFood::OnSphereBeginOverlap);
    	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AFood::OnSphereEndOverlap);
	}
	// Setup the interact key for the character to be able to pickup the food
	if(InputComponent)
		InputComponent->BindAction("Interact", IE_Pressed,this,&AFood::InteractKeyPressed);
}

void AFood::SetFoodProperties(EFoodState State)
{
	switch (State)
	{
		case EFoodState::EFS_PickedUp:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(false);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//Set AreaSphere properties
			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EFoodState::EFS_Dropped:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//Set AreaSphere properties
			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			break;
		default:
			//Set mesh properties
			StaticMesh->SetSimulatePhysics(true);
			StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//Set AreaSphere properties
			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			break;
	}
}

void AFood::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if(Hero)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Enable Input"));
		EnableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	}
	
}

void AFood::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if(Hero)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Disable Input"));
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	}
}

void AFood::InteractKeyPressed()
{
	AHero* Hero = Cast<AHero>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,"Interact Key Pressed");
	if(Hero)
	{
		if(Hero->GetCarriedFood() == nullptr)
		{
			Hero->CarryFood(this);
		}
		else
		{
			Hero->DropFood();
		}
	}
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::SetFoodState(EFoodState State)
{
	FoodState = State;
	SetFoodProperties(State);
}

