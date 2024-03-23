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

	// Checks the status condition of door.
	bool IsDoorOpen();
	// Checks if door is in position to close.
	bool CanDoorBeLocked();

	// Called by BaseCharacter class when player try to acces the door.
	FName TryAccessToDoor();

	// Method that handle the door mechanic.
	void ActionDoor(bool action);
	
protected:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.

	// Door root component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Root")
    class USceneComponent* doorRootComponent;

	// Door Mesh.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* meshDoor;

	// Static door mesh, pivot point.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* meshPivot;

	// Key name necesary for unlocking the door.
	UPROPERTY(EditAnywhere, category = "Unlock Door", meta = (AllowPrivateAccess))
	FName keyToUnlock;

	// Control open state.
	UPROPERTY(EditAnywhere, category = "Unlock Door", meta = (AllowPrivateAccess))
	bool isOpen;

	// Physic constrains for physics door mechanics.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	class UPhysicsConstraintComponent* physicsConstrain;

	bool canBeLocked;
	bool doOnceSwing;

	float currentSwing;
	float prevSwing;

};
