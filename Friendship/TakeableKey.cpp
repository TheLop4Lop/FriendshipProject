// Fill out your copyright notice in the Description page of Project Settings.


#include "TakeableKey.h"

// Sets default values for this actor's properties
ATakeableKey::ATakeableKey()
{
    doorToUnlock = TEXT("None");

}

// Returns the Ket Tag to open an specific BaseDoor Class.
FName ATakeableKey::GetKeyNameUnlockDoor()
{
    return doorToUnlock;

}
