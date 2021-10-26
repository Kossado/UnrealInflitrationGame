// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

#include "GCCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveItem::AInteractiveItem():Super()
{
	//Set up static mesh
	Trigger = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Sphere Component")));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetSphereRadius(150.f);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void AInteractiveItem::DisableTrigger()
{
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveItem::OnSphereBeginOverlap);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AInteractiveItem::OnSphereEndOverlap);
	
}

void AInteractiveItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGCCharacter* Character = Cast<AGCCharacter>(OtherActor);
	if(Character != nullptr)
	{
		Character->OnEnterActor(this);
	}
}

void AInteractiveItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AGCCharacter* Character = Cast<AGCCharacter>(OtherActor);
	if(Character != nullptr)
	{
		Character->OnLeaveActor(this);
	}
}