// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetHideoutPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "StalkerController.h"
#include "BaseStalker.h"

UBTTask_GetHideoutPoint::UBTTask_GetHideoutPoint()
{
    NodeName = TEXT("Get Hideout Point");

}

// ExcecuteTask funtion, manages to find the the closest hideout point for the Stalker.
EBTNodeResult::Type UBTTask_GetHideoutPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetOwner() == nullptr || OwnerComp.GetBlackboardComponent() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    stalker = Cast<ABaseStalker>(OwnerComp.GetAIOwner()->GetPawn());
    if(stalker == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    if(stalker->GetHideoutPoints().Num() > 0)
    {
        FVector distanceDifference = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
        ATargetPoint* closerPoint = nullptr;
        for(int i = 0; i < stalker->GetHideoutPoints().Num(); i++)
        {
            FVector currentDistance = (stalker->GetActorLocation() - stalker->GetHideoutPoints()[i]->GetActorLocation());
            if(currentDistance.Size() < distanceDifference.Size())
            {
                distanceDifference = currentDistance;
                closerPoint = stalker->GetHideoutPoints()[i];
            }        
        }

        if(closerPoint)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("HideoutPoint"), closerPoint->GetActorLocation());
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;

}
