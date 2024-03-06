// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

UENUM(BlueprintType)
enum class ECameraMovement : uint8
{
	IDLE,
	WALKING,
	SPRINTING
};

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API ABaseCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetCamerastateMovement(ECameraMovement movement);

protected:
	APawn* Pawn;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> idle;

	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> walking;

	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> sprint;

	TSubclassOf<UCameraShakeBase>* cameraState;

	void StartCameraMovement();

};
