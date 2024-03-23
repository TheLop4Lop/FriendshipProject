// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightController.generated.h"

DECLARE_DELEGATE_OneParam(FLightOverlap, bool);

UCLASS()
class FRIENDSHIP_API ALightController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FLightOverlap currentOvelap;

protected:
	// Holds all instances of TriggerLuminare on the world.
	TArray<class ATriggerLuminaire*> luminaireOnWorld;

	class ATriggerLuminaire* currentOvelappedLuminaire;

};
