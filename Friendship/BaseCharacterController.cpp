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
