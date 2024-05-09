// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressEventManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FProgressEvent, FName, bool&);

UCLASS()
class FRIENDSHIP_API AProgressEventManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressEventManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FProgressEvent changeStatus;

protected:
	////////////////////////////////////////////// MANAGER PPROPERTIES SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to ProgressEventManager class.
	UPROPERTY(EditAnywhere, Category = "Actor Propertie", meta = (AllowPrivateAccess))
	class UBoxComponent* boxEvent;

	// Reference to player, maybe to be removed.
	class ABaseCharacter* character;

	// Holds the name of the last key picked by the player.
	FName prevKey;

	// Controls the flow of the interection.
	bool doOnce;

	////////////////////////////////////////////// MANAGER EVENT SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to ProgressEventManager events on gameplay.

	// Stalker class to ve spawned when last key meets condition.
	UPROPERTY(EditAnywhere, Category = "Events", meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseStalker> stalkerClass;

	// Target points to help spawn locations through gameplay.
	UPROPERTY(EditAnywhere, Category = "Events", meta = (AllowPrivateAccess))
	TArray<class ATargetPoint*> spawnPoints;

	// Key name needed to spawn stalker on event.
	UPROPERTY(EditAnywhere, Category = "Events", meta = (AllowPrivateAccess))
	TArray<FName> keySpawnEvents;

	UPROPERTY(EditAnywhere, Category = "Events", meta = (AllowPrivateAccess))
	TArray<FName> lockActorsOnMap;

	// Checks the last key picked by the player and sets different conditions on gameplay.
	void SetEventBasedOnLastKey(FName lastKey);

	// Spawn Stalker on lastKey condition.
	void SpawnStalker(FName lastKey);

};
