#include "Torch.h"

ATorch::ATorch() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	//Set up Scene Component
	// SceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	// RootComponent = SceneComponent;

	//Set up static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));
	RootComponent = StaticMesh;
	// StaticMesh->SetupAttachment(RootComponent);
	

	//Set up light
	LightMesh = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("Light Mesh")));
	LightMesh->SetupAttachment(RootComponent);
}

void ATorch::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

