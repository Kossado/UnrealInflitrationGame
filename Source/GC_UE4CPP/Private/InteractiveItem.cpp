// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root Component")));
	RootComponent = RootScene;
	Trigger = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Sphere Component")));
	Trigger->SetupAttachment(RootScene);
	Trigger->SetSphereRadius(100.f);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	StaticMesh->SetupAttachment(RootScene);

}

// Called when the game starts or when spawned
void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<AGCPlayerCharacter>(OtherActor);

	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnEnterActor(this);
		OnPlayerBeginOverlap();
	}
}

void AInteractiveItem::OnPlayerBeginOverlap()
{
}

void AInteractiveItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnLeaveActor();
		OnPlayerBeginOverlap();
	}
}

FName AInteractiveItem::GetName()
{
	return ItemName;
}

void AInteractiveItem::OnInteract_Implementation()
{
	if(bItemCollected)
	{
		return;
	}
	if(PlayerCharacter != nullptr)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, "OnInteract");
		}
		if(!PlayerCharacter->HasItem())
		{
			PlayerCharacter->GrabItem(ItemClass);
			bItemCollected = true;
			OnItemCollected();
		}
	}
}

