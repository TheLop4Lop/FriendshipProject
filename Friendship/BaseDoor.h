// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDoor.generated.h"

UCLASS()
class FRIENDSHIP_API ABaseDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TryAccessToDoor(class ABaseCharacter* character);

protected:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, category = "Unlock Door", meta = (AllowPrivateAccess))
	FName keyToUnlock;

};
