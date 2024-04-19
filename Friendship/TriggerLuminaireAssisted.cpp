// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLuminaireAssisted.h"
#include "Components/PointLightComponent.h"

ATriggerLuminaireAssisted::ATriggerLuminaireAssisted()
{
    lightTypeAssist = CreateDefaultSubobject<UPointLightComponent>(TEXT("Assist Luminarie Mesh"));
    lightTypeAssist->SetupAttachment(luminarieMesh);

}

// Set the light intensity by the actor.
void ATriggerLuminaireAssisted::SetLigthing(bool light)
{
	if(light)
	{
		lightType->SetIntensity(maxLight);
        lightTypeAssist->SetIntensity(maxLight);
	}else
	{
		lightType->SetIntensity(minLight);
        lightTypeAssist->SetIntensity(minLight);
	}

}
