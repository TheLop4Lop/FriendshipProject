// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressEventManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BaseCharacter.h"
#include "BaseStalker.h"

// Sets default values
AProgressEventManager::AProgressEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxEvent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Event"));
	boxEvent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProgressEventManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), allActors);
	for(AActor* singleActor : allActors)
	{
		if(singleActor && singleActor->ActorHasTag(TEXT("Spawn"))) spawnPoints.Add(Cast<ATargetPoint>(singleActor));
	}
	UE_LOG(LogTemp, Display, TEXT("Spawn point on map: %i"), spawnPoints.Num());
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	doOnce = true;
	
}

// Called every frame
void AProgressEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(character)
	{
		if(boxEvent->IsOverlappingActor(character) && doOnce)
		{
			SetEventBasedOnLastKey(character->LastPickedKey());
			doOnce = false;
		}
		
		if(!prevKey.IsEqual(character->LastPickedKey())) doOnce = true;
		prevKey = character->LastPickedKey();
	}

}

// Checks the last key picked by the player and sets different conditions on gameplay.
void AProgressEventManager::SetEventBasedOnLastKey(FName lastKey)
{
	SpawnStalker(lastKey);

	bool changeStatusTo = false;
	for(FName singleEvent : lockActorsOnMap)
	{
		(singleEvent.IsEqual(lastKey))? changeStatusTo = false : changeStatusTo = true;
		break;
	}

	changeStatus.Broadcast(character->LastPickedKey(), changeStatusTo);

}

// Spawn Stalker on lastKey condition.
void AProgressEventManager::SpawnStalker(FName lastKey)
{
    ATargetPoint* spawnPoint = nullptr;
    for (ATargetPoint* singlePoint : spawnPoints)
    {
        if (singlePoint && singlePoint->ActorHasTag(lastKey))
        {
            spawnPoint = singlePoint;
            break;
        }
    }

    if (spawnPoint && keySpawnEvents.Contains(lastKey))
    {
        GetWorld()->SpawnActor<ABaseStalker>(stalkerClass, spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation());
    }

}
