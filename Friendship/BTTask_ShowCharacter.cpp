// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShowCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "StalkerController.h"
#include "BaseStalker.h"

UBTTask_ShowCharacter::UBTTask_ShowCharacter()
{
    NodeName = TEXT("Show Stalker");

}

// ExcecuteTask funtion, manages to show Stalker Character when arrives to stalker point.
EBTNodeResult::Type UBTTask_ShowCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{   
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetOwner() == nullptr || OwnerComp.GetBlackboardComponent() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    stalker = Cast<ABaseStalker>(OwnerComp.GetAIOwner()->GetPawn());
    if(stalker)
    {
        stalker->SetCharacterVisibility(false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsHidden"), false);
        return EBTNodeResult::Succeeded;
    }
    
    return EBTNodeResult::Failed;

}
