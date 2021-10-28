#include "Items/Torch.h"

ATorch::ATorch() : Super()
{
	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	RootComponent = StaticMesh;	

	//Set up light
	LightMesh = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("Light Mesh")));
	LightMesh->SetupAttachment(RootComponent);
}

void ATorch::BeginPlay()
{
	Super::BeginPlay();
}