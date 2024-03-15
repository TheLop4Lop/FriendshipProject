// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

// Enum that holds the values that the Camera Shake Class may react.
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
	// Method called by the BaseCharacter class, indicates the new movement status.
	void SetCamerastateMovement(ECameraMovement movement);

	// Method that manages mouse events, used for Widgets.
	void SetMouseConfigurationEvents(bool bEvent, float anxiety);

protected:
	APawn* Pawn;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	////////////////////////////////////////////// Movement SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character movement camera mechanic.

	// Shake camera class, Matinee Pointer, IDLE.
	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> idle;

	// Shake camera class, Matinee Pointer, WALKING.
	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> walking;

	// Shake camera class, Matinee Pointer, SPRINT.
	UPROPERTY(EditAnywhere, Category = "Camera Shake Movement", meta = (AllowPrivateAccess))
	TSubclassOf<UCameraShakeBase> sprint;

	// Pointer that holds the Shake Camera Pointer class, this will change depends on character actions.
	TSubclassOf<UCameraShakeBase>* cameraState;

	// Method tha manages the changes of movement on the cameraState pointer.
	void StartCameraMovement();
	
	////////////////////////////////////////////// Anxiety mouse SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character anxiety mouse-widget mechanic.

	// Determines how many times the mouse is going to try stay in his coordinates, this is determined by random coordinates.
	UPROPERTY(EditAnywhere, Category = "Mouse Rate Movement", meta = (AllowPrivateAccess))
	float mouseAnxietyRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Mouse Rate Movement", meta = (AllowPrivateAccess))
	float mousePositionX = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Mouse Rate Movement", meta = (AllowPrivateAccess))
	float mousePositionY = 90.0f;

	// Holds the anxiety on player when starts interaction with widget.
	float anxietyOnPlayer;

	// Control Widget state.
	bool usingWidget;
	// Control do Once state.
	bool doOnceAnxiety;

	// Timer that controls the anxiety rate callback, this is detemined by anxiety on player.
	FTimerHandle anxietyTimer;

	void ManageMouseAnxiety();

};
