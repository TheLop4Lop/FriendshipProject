// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDestructible.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseDestructible::ABaseDestructible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseDestructible::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(TagDestroyableActor);
	
}

// Called every frame
void ABaseDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when actor is being hit, it manages the damage taken by an actor.
float ABaseDestructible::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float damageIn = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	resistance -= damageIn;
	if(resistance <= 0)
	{
		Destroy();
	}
	
	return damageIn;

}
