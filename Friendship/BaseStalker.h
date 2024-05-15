// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseStalker.generated.h"

UCLASS()
class FRIENDSHIP_API ABaseStalker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseStalker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets the colission condition and hidden state of the character.
	void SetCharacterVisibility(bool bVisibility);

	// Retrieve the hideout points on the map.
	TArray<class AHidePoint*> GetHideoutPoints();

	// Retrieve the stalker points on the map.
	TArray<class AStalkPoint*> GetStalkerPoints();

protected:
	////////////////////////////////////////////// AI PROPERTIES SECTION //////////////////////////////////////////////
	// This section contains properties related to AI mechanics.

	// Stores the hideout points on the map.
	UPROPERTY(EditAnywhere, Category = "AI Movement", meta = (AllowPrivateAccess))
	TArray<class AHidePoint*> hideoutPoints;

	// Stores the stalker points on the map.
	UPROPERTY(EditAnywhere, Category = "AI Movement", meta = (AllowPrivateAccess))
	TArray<class AStalkPoint*> stalkerPoints;

	class AStalkerController* stalkerController;

};
