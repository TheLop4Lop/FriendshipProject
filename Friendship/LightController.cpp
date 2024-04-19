// Fill out your copyright notice in the Description page of Project Settings.


#include "LightController.h"
#include "Kismet/GameplayStatics.h"
#include "TriggerLuminaire.h"

// Sets default values
ALightController::ALightController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerLuminaire::StaticClass(), actorsInWorld);
	
	UE_LOG(LogTemp, Display, TEXT("Light Actors in world: %i"), actorsInWorld.Num());

	for(AActor* singleActor : actorsInWorld)
	{
		ATriggerLuminaire* luminaire = Cast<ATriggerLuminaire>(singleActor);
		if(luminaire)
		{
			luminaireOnWorld.Add(luminaire);
		}
	}

}

// Called every frame
void ALightController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for(ATriggerLuminaire* singleLuminaire : luminaireOnWorld)
	{
		if(singleLuminaire->IsTriggerBeingOverlapped())
		{
			currentOvelappedLuminaire = singleLuminaire;
			currentOvelap.ExecuteIfBound(false);
		}
	}

	if(currentOvelappedLuminaire)
	{
		if(!currentOvelappedLuminaire->IsTriggerBeingOverlapped())
		{
			currentOvelap.ExecuteIfBound(true);
		}
	}

}
