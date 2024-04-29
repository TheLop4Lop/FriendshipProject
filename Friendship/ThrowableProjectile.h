// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTakeable.h"
#include "ThrowableProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API AThrowableProjectile : public ABaseTakeable
{
	GENERATED_BODY()

public:
	AThrowableProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	////////////////////////////////////////////// Damage SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to actor damage mechanic.

	UPROPERTY(EditAnywhere, Category = "Throwable Damage", meta = (AllowPrivateAccess))
	class UProjectileMovementComponent* projectileComponent;

	UPROPERTY(EditAnywhere, Category = "Throwable Damage", meta = (AllowPrivateAccess))
	float damageAmount = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Throwable Durability", meta = (AllowPrivateAccess))
	float durabilityAmount = 5.0f;

	// Delegate function, interacts with object in the world, binded on BeginPlay method. Gets the parameters from hit event.
	UFUNCTION() 
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void ManageThrowableDurability();

};
