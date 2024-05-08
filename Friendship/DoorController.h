// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorController.generated.h"

UCLASS()
class FRIENDSHIP_API ADoorController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	////////////////////////////////////////////// DOOR ACTORS SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to BaseDoor class actors in the world.

	// Holds all the doors in the world.
	TArray<class ABaseDoor*> allDoors;

	////////////////////////////////////////////// PROGRESS MANAGER SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to ProgressEventManager class.

	// Pointer to the manager event on the world.
	class AProgressEventManager* manager;

	// Method binded by multicast delegate from AProgressEventManager class
	void ChangeDoorStatusEvent(FName lastKey, bool newStatus);

};
