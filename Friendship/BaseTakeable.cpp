// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTakeable.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseTakeable::ABaseTakeable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void ABaseTakeable::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(TagTakeableActor);
	
}

// Called every frame
void ABaseTakeable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Method that handles the take action of player.
ETakeableType ABaseTakeable::GetTypeOfTakeable()
{
	return takeableType;

}

// Method that return the quantity of actor, this depends on the type.
int ABaseTakeable::GetQuanityOfTakeable()
{
	switch (takeableType)
	{
		case ETakeableType::KEY:
            return minQuantity;
            break;

        case ETakeableType::BATTERY:
            return minQuantity;
            break;

		case ETakeableType::THROWABLE:
            return FMath::RandRange(minQuantity, maxQuantity);
            break;
        
        default:
            break;
	}

	return 0;
}

// Method that handle the detroy of the object.
void ABaseTakeable::DestroyTakeable()
{
	Destroy();
	
}
