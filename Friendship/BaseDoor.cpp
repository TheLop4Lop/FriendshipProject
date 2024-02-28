// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "BaseCharacter.h"

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

}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseDoor::TryAccessToDoor(class ABaseCharacter* character)
{
	ABaseCharacter* playerCharacter = character;
	if(playerCharacter)
	{
		if(playerCharacter->HasKeyToOpenDoor(keyToUnlock))
		{
			OpenDoor();
			UE_LOG(LogTemp, Display, TEXT("Please sir! Enter to the chambers!"));
		}else if(!isOpen)
		{
			playerCharacter->SituationDialog("I don't have the key for this door.");
		}
	}

}

void ABaseDoor::OpenDoor()
{
	isOpen = true;
	meshDoor->SetSimulatePhysics(isOpen);

}

bool ABaseDoor::IsDoorOpen()
{
	return isOpen;

}