#include "Item.h"

AItem::AItem()
{
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	RootComponent = StaticMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}
