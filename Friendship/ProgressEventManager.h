// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressEventManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FProgressEvent, FName, bool);

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

};
