// Fill out your copyright notice in the Description page of Project Settings.


#include "LightController.h"
#include "Kismet/GameplayStatics.h"
#include "ProgressEventManager.h"
#include "TriggerLuminaire.h"

// Sets default values
ALightController::ALightController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerLuminaire::StaticClass(), actorsInWorld);
	for(AActor* singleActor : actorsInWorld)
	{
		if(singleActor) luminaireOnWorld.Add(Cast<ATriggerLuminaire>(singleActor));
	}

	TArray<AActor*> managersInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProgressEventManager::StaticClass(), managersInWorld);
	if(managersInWorld.Num() > 0) manager = Cast<AProgressEventManager>(managersInWorld[0]);

	if(manager)
	{
		manager->changeStatus.AddUObject(this, &ALightController::ChangeLightStatusEvent);
	}

}

// Called every frame
void ALightController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(ATriggerLuminaire* singleLuminaire : luminaireOnWorld)
	{
		if(singleLuminaire->IsTriggerBeingOverlapped())
		{
			currentOvelappedLuminaire = singleLuminaire;
			currentOvelap.ExecuteIfBound(false);
		}
	}

	if(currentOvelappedLuminaire)
	{
		if(!currentOvelappedLuminaire->IsTriggerBeingOverlapped())
		{
			currentOvelap.ExecuteIfBound(true);
		}
	}

}

// Method binded by multicast delegate from AProgressEventManager class
void ALightController::ChangeLightStatusEvent(FName lastKey, bool& newStatus)
{
	for(ATriggerLuminaire* singleLuminaire : luminaireOnWorld)
	{
		if(singleLuminaire && singleLuminaire->ActorHasTag(lastKey))
		{
			singleLuminaire->ChangeLight(newStatus);
		}
	}

}
