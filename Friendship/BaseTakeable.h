// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTakeable.generated.h"

// Enums that hepls determine the type of actor in the world, also to know how many of this should be given to the player.
UENUM(BlueprintType)
enum class ETakeableType : uint8
{
	KEY,
	BATTERY,
	THROWABLE
};

UCLASS()
class FRIENDSHIP_API ABaseTakeable : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseTakeable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Method that returns the type of actor in the world.
	ETakeableType GetTypeOfTakeable();
	// Method that return the quantity of actor, this depends on the type.
	int GetQuanityOfTakeable();
	// Method that handle the detroy of the object.
	void DestroyTakeable();

protected:
	////////////////////////////////////////////// Properties SECTION //////////////////////////////////////////////
	// This section contains properties related to actor.
	UPROPERTY(EditAnywhere, Category = "Actor Mesh", meta = (AllowPrivateAccess))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Generation Properties", meta = (AllowPrivateAccess))
	int minQuantity = 1;

	UPROPERTY(EditAnywhere, Category = "Generation Properties", meta = (AllowPrivateAccess))
	int maxQuantity = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Takeable Type", meta = (AllowPrivateAccess))
	ETakeableType takeableType;

	// Variables of controll, determine the kind of interanction of an actor in the world.
	FName TagTakeableActor = FName("Takeable");

};
