#include "Item.h"

AItem::AItem():Super()
{
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}
