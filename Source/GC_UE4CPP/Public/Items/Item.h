#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM()
enum EItemState
{
	EIS_Movable,
	EIS_Interacting,
	EIS_Immovable,
	EIS_Disabled,
};

UCLASS()
class GC_UE4CPP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void SetItemProperties(EItemState State);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Mesh")
	UStaticMeshComponent* StaticMesh;
	
	EItemState CurrentItemState;

public:	
	FORCEINLINE UStaticMeshComponent* GetItemMesh() const {return StaticMesh;}
	FORCEINLINE EItemState GetCurrentItemState() const { return CurrentItemState; }

private:

};
