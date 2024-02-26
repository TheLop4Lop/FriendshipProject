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

void ATriggerLuminaire::BeginPlay()
{
    Super::BeginPlay();
    character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

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
    if(anxietyBox->IsOverlappingActor(character) && !isLightOn && doOnceTimer)
    {
        anxietyDelagate.BindLambda([this](){
            character->IncreaseAnxietyOnCharacter();
        });

        ManageCharacterOnTrigger();
        doOnceTimer = false;
    }else if (!anxietyBox->IsOverlappingActor(character) && !character->isCharacterSptinting() && !doOnceTimer)
    {
        anxietyDelagate.BindLambda([this](){
            if(character->GetAnxietyLevel() <= 0.0f)
            {
                GetWorldTimerManager().ClearTimer(anxietyTimer);
            }

            character->DecreaseAnxietyOnCharacter();
        });

        ManageCharacterOnTrigger();
        doOnceTimer = true;
    }

}

void ATriggerLuminaire::ManageCharacterOnTrigger()
{
    GetWorldTimerManager().ClearTimer(anxietyTimer);
    GetWorldTimerManager().SetTimer(anxietyTimer, anxietyDelagate, character->GetAnxietyPeriod(), true);

}