// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightController.generated.h"

DECLARE_DELEGATE_OneParam(FLightOverlap, bool);

UCLASS()
class FRIENDSHIP_API ALightController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FLightOverlap currentOvelap;

protected:
	////////////////////////////////////////////// LIGHT CONTROLLER PPROPERTIES SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to LightController class.

	// Holds all instances of TriggerLuminare on the world.
	TArray<class ATriggerLuminaire*> luminaireOnWorld;

	// Holds a pointer to the current overlapped Luminaire by the player.
	class ATriggerLuminaire* currentOvelappedLuminaire;

	////////////////////////////////////////////// PROGRESS MANAGER SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to ProgressEventManager class.

	// Pointer to the manager event on the world.
	class AProgressEventManager* manager;

	// Method binded by multicast delegate from AProgressEventManager class
	void ChangeLightStatusEvent(FName lastKey, bool& newStatus);

};
