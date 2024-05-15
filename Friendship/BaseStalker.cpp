// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStalker.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StalkerController.h"
#include "StalkPoint.h"
#include "HidePoint.h"

// Sets default values
ABaseStalker::ABaseStalker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseStalker::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHidePoint::StaticClass(), allActors);
	for(AActor* singleHidePoint : allActors)
	{
		if(singleHidePoint) hideoutPoints.Add(Cast<AHidePoint>(singleHidePoint));
	}

	allActors.Empty();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStalkPoint::StaticClass(), allActors);
	for(AActor* singleHidePoint : allActors)
	{
		if(singleHidePoint) stalkerPoints.Add(Cast<AStalkPoint>(singleHidePoint));
	}
	
	stalkerController = GetWorld()->SpawnActor<AStalkerController>(AIControllerClass, GetActorLocation(), GetActorRotation());
	if(stalkerController)
	{
		stalkerController->Possess(this);
	}

}

// Called every frame
void ABaseStalker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseStalker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Sets the colission condition and hidden state of the character.
void ABaseStalker::SetCharacterVisibility(bool bVisibility)
{
	SetActorHiddenInGame(bVisibility);
	(bVisibility)? GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision) 
					: GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Retrieve the hideout points on the map.
TArray<AHidePoint*> ABaseStalker::GetHideoutPoints()
{
    return hideoutPoints;

}

// Retrieve the stalker points on the map.
TArray<AStalkPoint*> ABaseStalker::GetStalkerPoints()
{
	return stalkerPoints;

}
