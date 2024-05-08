// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetStalkPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "StalkerController.h"
#include "BaseStalker.h"

UBTTask_GetStalkPoint::UBTTask_GetStalkPoint()
{
    NodeName = TEXT("Get Stalk Point");

}

// ExcecuteTask funtion, manages to find the the closest stalk point for the Stalker.
EBTNodeResult::Type UBTTask_GetStalkPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
    
    if(stalker->GetStalkerPoints().Num() > 0)
    {
        FVector distanceDifference = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
        ATargetPoint* closerPoint = nullptr;
        for(int i = 0; i < stalker->GetStalkerPoints().Num(); i++)
        {
            FVector currentDistance = (stalker->GetActorLocation() - stalker->GetStalkerPoints()[i]->GetActorLocation());
            if(currentDistance.Size() < distanceDifference.Size())
            {
                distanceDifference = currentDistance;
                closerPoint = stalker->GetStalkerPoints()[i];
            }        
        }

        if(closerPoint)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("StalkPoint"), closerPoint->GetActorLocation());
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;

}
