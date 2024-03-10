// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLuminaire.h"
#include "TriggerLuminaire.generated.h"

float const Zero = 0; // Zero value const.

UCLASS()
class FRIENDSHIP_API ATriggerLuminaire : public ABaseLuminaire
{
	GENERATED_BODY()

public:	
	ATriggerLuminaire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	////////////////////////////////////////////// ANXIETY SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character anxiety mechanic.
	UPROPERTY(EditAnywhere, Category = "Trigger Property", meta = (AllowPrivateAccess))
	class UBoxComponent* anxietyBox;

	// Manages the anxiety on Player Character, depends if light is active or not.
	void SetAnxietyFunctionality();
	// Method that manages the timer setting on anxietyTimer.
	void ManageCharacterOnTrigger();

	// Stores the player character.
	class ABaseCharacter* character;
	TArray<AActor*> Actors;

	// Timer that handles the anxiey timer on the player.
	FTimerHandle anxietyTimer;
	// Timer delagate that calls anxiety on BaseCharacter.
	FTimerDelegate anxietyDelagate;

	// Control bool timer state.
	bool doOnceTimer = true;

};
