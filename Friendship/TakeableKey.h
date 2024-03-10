// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTakeable.h"
#include "TakeableKey.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API ATakeableKey : public ABaseTakeable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATakeableKey();

	// Returns the Ket Tag to open an specific BaseDoor Class.
	FName GetKeyNameUnlockDoor();

private:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.

	// Variable that stores Key tag to open an specific BaseDoor class.
	UPROPERTY(EditAnywhere, Category = "Unlock Door", meta = (AllowPrivateAccess))
	FName doorToUnlock;
	
};
