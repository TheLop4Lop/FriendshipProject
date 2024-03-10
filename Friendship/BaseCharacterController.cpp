// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterController.h"
#include "GameFramework/PlayerInput.h"
#include "BaseCharacter.h"
#include "Engine.h"

//BeginPlay defines the initial value of the funtion pointers, this pointers define the behaviour of the movement.
void ABaseCharacterController::BeginPlay()
{
    Pawn = GetPawn();

}

//Binding Axis and Action Mapping.
void ABaseCharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

}

////////////////////////////////////////////// Movement SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character movement camera mechanic.

// Method tha manages the changes of movement on the cameraState pointer.
void ABaseCharacterController::SetCamerastateMovement(ECameraMovement movement)
{
    if(idle && walking && sprint)
    {
        switch(movement)
        {
            case ECameraMovement::IDLE:
                cameraState = &idle;
                break;
            case ECameraMovement::WALKING:
                cameraState = &walking;
                break;
            case ECameraMovement::SPRINTING:
                cameraState = &sprint;
                break;

            default:
                cameraState = nullptr;
                break;
        }
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Movement Camera Class defined!"));
    }

    StartCameraMovement();

}

// Method tha manages the changes of movement on the cameraState pointer.
void ABaseCharacterController::StartCameraMovement()
{
    if(cameraState)
    {
        ClientStartCameraShake(*cameraState);
    }

}
