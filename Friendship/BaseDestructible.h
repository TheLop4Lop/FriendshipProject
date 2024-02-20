// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDestructible.generated.h"

UCLASS()
class FRIENDSHIP_API ABaseDestructible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDestructible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when actor is being hit, it manages the damage taken by an actor.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Actor Capsule", meta = (AllowPrivateAccess))
	class UCapsuleComponent* Capsule;

	// Value that represents the total resistance or 'life' amount of the actor.
	UPROPERTY(EditAnywhere, Category = "Actor Resistance", meta = (AllowPrivateAccess))
	float resistance = 5.0f;

	// Variables of controll, determine the kind of interanction of an actor in the world.
	FName TagDestroyableActor = FName("Destroy");
	
};
