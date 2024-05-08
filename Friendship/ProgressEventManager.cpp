// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressEventManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

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
			changeStatus.Broadcast(character->LastPickedKey(), false);
			doOnce = false;
		}
		
		if(!prevKey.IsEqual(character->LastPickedKey())) doOnce = true;
		prevKey = character->LastPickedKey();
	}

}
