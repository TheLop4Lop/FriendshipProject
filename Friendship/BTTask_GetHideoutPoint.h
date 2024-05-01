// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetHideoutPoint.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API UBTTask_GetHideoutPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetHideoutPoint();

protected:
	////////////////////////////////////////////// HIDEOUT POINTS SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to Stalker hideout Points.

	// ExcecuteTask funtion, manages to find the the closest hideout point for the Stalker.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Reference Stalker pointer.
	class ABaseStalker* stalker;

};
