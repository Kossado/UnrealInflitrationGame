#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class GC_UE4CPP_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetValidStoredPosition();

private:
	UPROPERTY(VisibleAnywhere, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChestMesh;

	UPROPERTY(VisibleAnywhere, Category=Storing, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Storing, meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> FoodPlaceholder;

};
