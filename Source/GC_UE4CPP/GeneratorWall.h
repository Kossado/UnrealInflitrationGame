#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratorWall.generated.h"

UENUM()
enum Axe
{
	AxeX UMETA(DisplayName = "Axe X"),
	AxeY UMETA(DisplayName = "Axe Y"),
	AxeZ UMETA(DisplayName = "Axe Z"),
};

UCLASS()


class GC_UE4CPP_API AGeneratorWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AGeneratorWall();

	UPROPERTY(EditAnywhere)
	int NumberWallX;

	UPROPERTY(EditAnywhere)
	int NumberWallY;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* WallPrefab;

private:
	USceneComponent* SceneComponent;
	
	void CreateWall(FVector positionDepart);
	
public:	
	UFUNCTION(CallInEditor)
	void CreateWallFromEditor();
	
	void CreateWallFromPlay();
	
};
