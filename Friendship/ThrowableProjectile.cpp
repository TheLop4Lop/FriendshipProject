// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AThrowableProjectile::AThrowableProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

}

void AThrowableProjectile::BeginPlay()
{
    Super::BeginPlay();

    if(GetInstigator())
    {
        FCollisionQueryParams params;
        params.AddIgnoredActor(GetInstigator());
    }

    Mesh->OnComponentHit.AddDynamic(this, &AThrowableProjectile::OnHit);

}

void AThrowableProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Display, TEXT("HIT DETECTED"));

    TSubclassOf<UDamageType> damageTypeClass = UDamageType::StaticClass();

    if( GetInstigator()->GetInstigatorController())
    {
        UGameplayStatics::ApplyDamage(OtherActor, damageAmount, GetInstigator()->GetInstigatorController(), this, damageTypeClass);
    }

    ManageThrowableDurability();

}

void AThrowableProjectile::ManageThrowableDurability()
{
    durabilityAmount--;

    if(durabilityAmount <= 0)
    {
        UE_LOG(LogTemp, Display, TEXT("I'M DESTROYED!"));
        Destroy();
    }

}
