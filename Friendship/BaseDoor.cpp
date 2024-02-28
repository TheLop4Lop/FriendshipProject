// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoor.h"
#include "BaseCharacter.h"

// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
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
			UE_LOG(LogTemp, Display, TEXT("Please sir! Enter to the chambers!"));
		}else
		{
			playerCharacter->SituationDialog("I don't have the key for this door.");
		}
	}

}
