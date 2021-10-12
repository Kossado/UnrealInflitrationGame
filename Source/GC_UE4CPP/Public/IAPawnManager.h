
#pragma once

#include "CoreMinimal.h"
#include "IAPatrolPoint.h"
#include "GameFramework/Actor.h"

#include "IAPawnManager.generated.h"

UCLASS(Abstract)
class GC_UE4CPP_API AIAPawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAPawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	AIAPatrolPoint* UnSpawnAIPatrolPoint;

private:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UnSpawnIA(AActor* UnSpawnIA); 

};
