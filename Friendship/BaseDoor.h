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

	bool IsDoorOpen();
	void TryAccessToDoor(class ABaseCharacter* character);

protected:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Root")
    class USceneComponent* doorRootComponent;

	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* meshDoor;

	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* meshPivot;

	UPROPERTY(EditAnywhere, category = "Unlock Door", meta = (AllowPrivateAccess))
	FName keyToUnlock;

	UPROPERTY(EditAnywhere, category = "Unlock Door", meta = (AllowPrivateAccess))
	bool isOpen;

	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	class UPhysicsConstraintComponent* physicsConstrain;

	void OpenDoor();

};
