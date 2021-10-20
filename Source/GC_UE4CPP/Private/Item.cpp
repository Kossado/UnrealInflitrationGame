#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	//Set up Scene Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	RootComponent = SceneComponent;

	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	StaticMesh->SetupAttachment(RootComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

