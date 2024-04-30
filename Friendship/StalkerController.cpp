// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerController.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Kismet/GameplayStatics.h"

AStalkerController::AStalkerController()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStalkerController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior); // Sets the Behavior Tree selected by the player.
    }

    AIPerception = FindComponentByClass<UAIPerceptionComponent>();
    if(AIPerception)
    {
        UE_LOG(LogTemp, Display, TEXT("UAIPerceptionComponent FOUND!"));
        FAISenseID SenseIDSight = UAISense::GetSenseID<UAISense_Sight>(); // Gets the Sight sense ID for AiPerception config.
        Sight = Cast<UAISenseConfig_Sight>(AIPerception->GetSenseConfig(SenseIDSight)); // Gets the acual SenseConfigClass, with this perception can be modified.
        if(Sight)
        {
            Sight->DetectionByAffiliation.bDetectNeutrals = true;
        }

        AIPerception->ConfigureSense(*Sight);
        AIPerception->SetDominantSense(Sight->GetSenseImplementation()); // Gets from editor the configuration details from Sight Config.

        AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AStalkerController::OnTargetPerceptionUpdated);
    }

}

// Called every frame
void AStalkerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AStalkerController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    UE_LOG(LogTemp, Display, TEXT("Character on Sight!"));

}