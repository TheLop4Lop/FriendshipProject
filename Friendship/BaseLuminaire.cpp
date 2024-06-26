// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLuminaire.h"
#include "Components/PointLightComponent.h"

// Sets default values
ABaseLuminaire::ABaseLuminaire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	luminarieMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Luminarie Mesh"));
	luminarieMesh->SetupAttachment(RootComponent);

	lightType = CreateDefaultSubobject<UPointLightComponent>(TEXT("Luminarie"));
	lightType->SetupAttachment(luminarieMesh);

}

// Called when the game starts or when spawned
void ABaseLuminaire::BeginPlay()
{
	Super::BeginPlay();

	SetLigthing(isLightOn);
	lightPrevState = isLightOn;
	
}

// Called every frame
void ABaseLuminaire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isLightOn != lightPrevState)
	{
		SetLigthing(isLightOn);
		lightPrevState = isLightOn;
	}

}

// Set the light intensity by the actor.
void ABaseLuminaire::SetLigthing(bool light)
{
	(light)? lightType->SetIntensity(maxLight) : lightType->SetIntensity(minLight);
	isLightOn = light;

}

// Method in charge of actor visibility, due to reduce resources on gameplay.
void ABaseLuminaire::SetLuminaireVisibility(bool bVisibility)
{
	this->SetActorHiddenInGame(bVisibility);

}

// Method handle the change of light status.
void ABaseLuminaire::ChangeLight(bool lightStatus)
{
	SetLigthing(lightStatus);

}
