// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HideCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "StalkerController.h"
#include "BaseStalker.h"

UBTTask_HideCharacter::UBTTask_HideCharacter()
{
    NodeName = TEXT("Hide Stalker");

}

// ExcecuteTask funtion, manages to hid Stalker Character when arrives to hideout point.
EBTNodeResult::Type UBTTask_HideCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{   
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetOwner() == nullptr || OwnerComp.GetBlackboardComponent() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    stalker = Cast<ABaseStalker>(OwnerComp.GetAIOwner()->GetPawn());
    if(stalker)
    {
        stalker->SetCharacterVisibility(true);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsHidden"), true);
        return EBTNodeResult::Succeeded;
    }
    
    return EBTNodeResult::Failed;

}
