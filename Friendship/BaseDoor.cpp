// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(doorRootComponent);

	meshPivot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pivot Mesh"));
	meshPivot->SetupAttachment(doorRootComponent);

	meshDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	meshDoor->SetupAttachment(meshPivot);

	physicsConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constrain"));
	physicsConstrain->SetupAttachment(doorRootComponent);

}

// Called when the game starts or when spawned
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();

	meshDoor->SetSimulatePhysics(isOpen);
	physicsConstrain->SetConstrainedComponents(meshPivot, TEXT("Pivot Mesh"), meshDoor, TEXT("Door Mesh"));
	canBeLocked = true;

}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(isOpen)
	{
		if(doOnceSwing)
		{
			prevSwing = physicsConstrain->GetCurrentSwing1();
			doOnceSwing = false;
		}
		
		currentSwing = physicsConstrain->GetCurrentSwing1();
		(currentSwing >=  prevSwing - 1.5f && currentSwing <=  prevSwing + 1.5f) ? canBeLocked = true : canBeLocked = false;
	}

}

// Called by BaseCharacter class when player try to acces the door.
FName ABaseDoor::TryAccessToDoor()
{
	return keyToUnlock;

}

// Method that handle the door mechanic.
void ABaseDoor::ActionDoor(bool action)
{
	isOpen = action;
	doOnceSwing = isOpen;
	meshDoor->SetSimulatePhysics(isOpen);

}

// Checks the status condition of door.
bool ABaseDoor::IsDoorOpen()
{
	return isOpen;

}

bool ABaseDoor::CanDoorBeLocked()
{
	return canBeLocked;

}