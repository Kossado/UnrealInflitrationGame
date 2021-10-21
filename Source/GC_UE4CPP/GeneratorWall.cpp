// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorWall.h"

// Sets default values
AGeneratorWall::AGeneratorWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Création de la scène
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("RootScene"));
    RootComponent = SceneComponent;	
}

// Called when the game starts or when spawned
void AGeneratorWall::BeginPlay()
{
	Super::BeginPlay();
}

// Génération d'un mur depuis l'éditeur
void AGeneratorWall::CreateWallFromEditor()
{
	
	CreateWall(GetActorLocation());
}

// Génération d'un mur depuis le lancement du jeu
void AGeneratorWall::CreateWallFromPlay()
{
	CreateWall(FVector(0,0,0));
}

// Génération d'un mur
void AGeneratorWall::CreateWall(FVector positionDepart)
{
	// On vérifie que le développeur à rentrée des informations correct
	if(WallPrefab == nullptr || WallPrefab->GetStaticMesh() == nullptr)
	{
		return;
	}

	// On supprime les instances déjà présentes s'il y en a
	if (WallPrefab->GetInstanceCount() != 0)
	{
		WallPrefab->ClearInstances();
	}

	// On définit les collisions des murs
	WallPrefab->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	WallPrefab->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WallPrefab->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	WallPrefab->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	// On récupère la taille du composant choisi
	FVector tailleComposant = WallPrefab->GetStaticMesh()->GetBounds().GetBox().GetSize();

	// On initialise les coordonné de départ du mur
	float posX;
	float posY = positionDepart.Y;
	float posZ = positionDepart.Z + tailleComposant.Z / 2;

	// Placement des différentes briques du murs
	for (int i = 0; i < NumberWallY; i++)
	{
		posX = positionDepart.X + tailleComposant.X / 2;
		for (int j = 0; j < NumberWallX; j++)
		{
			WallPrefab->AddInstance(FTransform(FVector(posX,posY,posZ)));
			posX += tailleComposant.X;
		}
		posZ += tailleComposant.Z;
	}
}

// Called every frame
void AGeneratorWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
