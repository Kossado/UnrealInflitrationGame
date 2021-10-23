// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GCPlayerCharacter.h"
#include "Interactable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "InteractiveItem.generated.h"

UCLASS()
class GC_UE4CPP_API AInteractiveItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Interactive")
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, Category="Interactive")
	USphereComponent* Trigger;
	UPROPERTY(VisibleAnywhere, Category="Interactive")
	UStaticMeshComponent* StaticMesh;
	AGCPlayerCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool bItemCollected;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void OnPlayerBeginOverlap();
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void OnPlayerEndOverlap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Events")
	void OnItemCollected();

	///////////////// INTERFACE IInteractable ///////////////////////
	
public:
	virtual FName GetName() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnInteract();

	void OnInteract_Implementation();
	
	///////////////// INTERFACE IInteractable ///////////////////////
};
