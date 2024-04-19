// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerLuminaire.h"
#include "TriggerLuminaireAssisted.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API ATriggerLuminaireAssisted : public ATriggerLuminaire
{
	GENERATED_BODY()

public:
	ATriggerLuminaireAssisted();

protected:
	// Luminarie type to be edited.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	class UPointLightComponent* lightTypeAssist;

	// Set the light intensity by the actor.
	virtual void SetLigthing(bool light) override;
	
};
