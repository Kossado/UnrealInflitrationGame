#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class GC_UE4CPP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category=Mesh)
	UStaticMeshComponent* StaticMesh;

public:	
	FORCEINLINE UStaticMeshComponent* GetItemMesh() const {return StaticMesh;}
	
};
