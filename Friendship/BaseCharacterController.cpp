// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterController.h"
#include "GameFramework/PlayerInput.h"
#include "Engine.h"

//BeginPlay defines the initial value of the funtion pointers, this pointers define the behaviour of the movement.
void ABaseCharacterController::BeginPlay()
{
    Pawn = GetPawn();
    doOnceAnxiety = true;

}

//Binding Axis and Action Mapping.
void ABaseCharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

}

void ABaseCharacterController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(usingWidget && doOnceAnxiety)
    {
        GetWorldTimerManager().ClearTimer(anxietyTimer);
        GetWorldTimerManager().SetTimer(anxietyTimer, this, &ABaseCharacterController::ManageMouseAnxiety, 
                                        mouseAnxietyRate/anxietyOnPlayer, usingWidget);
    
        doOnceAnxiety = false;
    }

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

// Method that manages mouse events, used for Widgets.
void ABaseCharacterController::SetMouseConfigurationEvents(bool bEvent, float anxiety)
{
    usingWidget = bEvent;
    bShowMouseCursor = bEvent;
    bEnableClickEvents = bEvent;
    bEnableMouseOverEvents = bEvent;

    anxietyOnPlayer = FMath::Clamp(anxiety, 1.0f, 100.0f);
    bEvent? SetInputMode(FInputModeGameAndUI()) : SetInputMode(FInputModeGameOnly());
    
}

// Method tha manages the changes of movement on the cameraState pointer.
void ABaseCharacterController::StartCameraMovement()
{
    if(cameraState)
    {
        ClientStartCameraShake(*cameraState);
    }

}

// Method that handles the Anxiety mouse movement event while interacting with door widget.
void ABaseCharacterController::ManageMouseAnxiety()
{
    float mouseX, mouseY;
    GetMousePosition(mouseX, mouseY);

    FVector2D mouseDirection = (mouseTarget - FVector2D(mouseX, mouseY)).GetSafeNormal();

    const float MovementScale = 0.1f;
    mouseX += mouseDirection.X * MovementScale;
    mouseY += mouseDirection.Y * MovementScale;

    const float ScreenWidth = 1920;
    const float ScreenHeight = 1080;
    const float zero = 0.0f;
    mouseX = FMath::Clamp(mouseX, zero, ScreenWidth);
    mouseY = FMath::Clamp(mouseY, zero, ScreenHeight);

    SetMouseLocation(mouseX, mouseY);
    
    doOnceAnxiety = true;

}
