// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorController.h"
#include "Kismet/GameplayStatics.h"
#include "ProgressEventManager.h"
#include "BaseDoor.h"

// Sets default values
ADoorController::ADoorController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseDoor::StaticClass(), actorsInWorld);
	for(AActor* singleActor : actorsInWorld)
	{
		if(singleActor) allDoors.Add(Cast<ABaseDoor>(singleActor));
	}

	TArray<AActor*> managersInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProgressEventManager::StaticClass(), managersInWorld);
	if(managersInWorld.Num() > 0) manager = Cast<AProgressEventManager>(managersInWorld[0]);

	if(manager)
	{
		manager->changeStatus.AddUObject(this, &ADoorController::ChangeDoorStatusEvent);
	}
	
}

// Called every frame
void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Method binded by multicast delegate from AProgressEventManager class
void ADoorController::ChangeDoorStatusEvent(FName lastKey, bool& newStatus)
{
	for(ABaseDoor* singleDoor : allDoors)
	{
		if(singleDoor && singleDoor->ActorHasTag(lastKey))
		{
			singleDoor->ActionDoor(newStatus);
		}
	}

}
