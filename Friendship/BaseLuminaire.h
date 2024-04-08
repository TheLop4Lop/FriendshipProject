// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLuminaire.generated.h"

UCLASS()
class FRIENDSHIP_API ABaseLuminaire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLuminaire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	////////////////////////////////////////////// LIGHT SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to Light behaviour.

	// Luminarie mesh.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* luminarieMesh;

	// Luminarie type to be edited.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	class UPointLightComponent* lightType;

	// Control light state.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	bool isLightOn = true;

	// Minimum value on the light actor.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	float minLight = 0.0f;

	// Maximum value on the light actor.
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	float maxLight = 10.0f;

	// Holds previus light state.
	bool lightPrevState;

	// Set the light intensity by the actor.
	void SetLigthing(bool light);

};
