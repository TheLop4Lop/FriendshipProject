// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "StalkerController.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API AStalkerController : public AAIController
{
	GENERATED_BODY()

public:
	AStalkerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	////////////////////////////////////////////// AI PROPERTIES SECTION //////////////////////////////////////////////
	// This section contains properties related to AI mechanics.

	// Stores a reference to the actual UBehaviorTree in charge of controlling the Stalker.
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowAccess))
	class UBehaviorTree* AIBehavior;

	// Sense configuration start, determines the initial sight parameters for the stalker.
	class UAISenseConfig_Sight* Sight;

	// Perception component, responsable fo holding the senses of the stalker.
	UPROPERTY(EditAnywhere, Category = "AI Perception", meta = (AllowPrivateAccess))
	class UAIPerceptionComponent* AIPerception;

	

};
