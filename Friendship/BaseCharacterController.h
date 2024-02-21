// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API ABaseCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	APawn* Pawn;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

};
