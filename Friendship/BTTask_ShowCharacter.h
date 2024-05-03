// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShowCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API UBTTask_ShowCharacter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ShowCharacter();

protected:
	////////////////////////////////////////////// STALK POINTS SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to Stalker stalk Points.

	// ExcecuteTask funtion, manages to show Stalker Character when arrives to stalker point.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	// Reference Stalker pointer.
	class ABaseStalker* stalker;

};
