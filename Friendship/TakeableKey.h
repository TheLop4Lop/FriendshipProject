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
	FName GetKeyNameUnlockDoor();

private:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.
	UPROPERTY(EditAnywhere, Category = "Unlock Door", meta = (AllowPrivateAccess))
	FName doorToUnlock;
	
};
