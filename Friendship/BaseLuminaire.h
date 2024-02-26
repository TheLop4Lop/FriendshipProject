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
	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	UStaticMeshComponent* luminarieMesh;

	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	class URectLightComponent* lightType;

	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	bool isLightOn = true;

	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	float minLight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Luminarie Properties", meta = (AllowPrivateAccess))
	float maxLight = 10.0f;

	bool lightPrevState;

	void SetLigthing(bool light);

};
