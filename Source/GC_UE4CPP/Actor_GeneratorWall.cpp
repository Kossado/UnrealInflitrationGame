// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_GeneratorWall.h"

// Sets default values
AActor_GeneratorWall::AActor_GeneratorWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Création de la scène
	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("RootScene"));
    RootComponent = SceneComponent;
	
}

// Called when the game starts or when spawned
void AActor_GeneratorWall::BeginPlay()
{
	Super::BeginPlay();
}

// Génération d'un mur depuis l'éditeur
void AActor_GeneratorWall::CreateWallFromEditor()
{
	
	CreateWall(GetActorLocation());
}

// Génération d'un mur depuis le lancement du jeu
void AActor_GeneratorWall::CreateWallFromPlay()
{
	CreateWall(FVector(0,0,0));
}

// Génération d'un mur
void AActor_GeneratorWall::CreateWall(FVector positionDepart)
{
	// On vérifie que le développeur à rentrée des informations correct
	if(UnWallPrefab == nullptr || UnWallPrefab->GetStaticMesh() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Veuillez sélectionné le mesh souhaitez");
		return;
	}

	// On supprime les instances déjà présentes s'il y en a
	if (UnWallPrefab->GetInstanceCount() != 0)
	{
		UnWallPrefab->ClearInstances();
	}

	// On récupère la taille du composant choisi
	FVector tailleComposant = UnWallPrefab->GetStaticMesh()->GetBounds().GetBox().GetSize();

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
			UnWallPrefab->AddInstance(FTransform(FVector(posX,posY,posZ)));
			posX += tailleComposant.X;
		}
		posZ += tailleComposant.Z;
	}
}

// Called every frame
void AActor_GeneratorWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
