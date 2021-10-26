#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class GC_UE4CPP_API AChest : public AInteractiveItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();
	FVector GetValidStoredPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category=Storing, meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> FoodPlaceholder;

};
