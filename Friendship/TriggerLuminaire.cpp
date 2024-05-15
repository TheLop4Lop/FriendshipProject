// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLuminaire.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

ATriggerLuminaire::ATriggerLuminaire() : ABaseLuminaire()
{
    anxietyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Anxiety Box"));
    anxietyBox->SetupAttachment(luminarieMesh);

}

// Called when the game starts or when spawned
void ATriggerLuminaire::BeginPlay()
{
    Super::BeginPlay();
    character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    doOnceOverlap = true;

}

// Called every frame
void ATriggerLuminaire::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(character)
    {
        SetAnxietyFunctionality();
    }

}

// Manages the anxiety on Player Character, depends if light is active or not.
void ATriggerLuminaire::SetAnxietyFunctionality()
{
    if(anxietyBox->IsOverlappingActor(character) && doOnceOverlap)
    {
        if(!isLightOn)
        {
            characterIsOverlaping = true;
        }

        doOnceOverlap = false;
    }else if (!anxietyBox->IsOverlappingActor(character) && !doOnceOverlap)
    {
        characterIsOverlaping = false;
        doOnceOverlap = true;
    }

}

// Returns the anxietyBox reference.
bool ATriggerLuminaire::IsTriggerBeingOverlapped()
{
    return characterIsOverlaping;

}
