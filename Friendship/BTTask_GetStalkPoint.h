// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetStalkPoint.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API UBTTask_GetStalkPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetStalkPoint();

protected:
	////////////////////////////////////////////// STALK POINTS SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to Stalker stalk Points.

	// ExcecuteTask funtion, manages to find the the closest stalk point for the Stalker.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Reference Stalker pointer.
	class ABaseStalker* stalker;
	
};
