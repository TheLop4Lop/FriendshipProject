// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

UENUM(BlueprintType)
enum class EInputType : uint8
{
	KEYBOARD_CONTROLLER,
	CONTROLLER_CONTROLLER,
	OCULUS_CONTROLLER
};

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API ABaseCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	EInputType GetPlayerControllerType();

protected:
	APawn* Pawn;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

};
