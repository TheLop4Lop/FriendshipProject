// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorWidget.generated.h"

DECLARE_DELEGATE(FExitConfig);

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API UDoorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Class constructor.
	virtual void NativeConstruct() override;

public:
	// Sets all the keys the player has.
	void SetKeysForDoorKnob(TArray<FName>& keyTags, FName currentDoor);

	// Opens door from BaseCharacter.
	bool CanOpenDoor();

	// Delegate to observer pattern, set knob exit conditions on BaseCharacter.
	FExitConfig knobEvent;

	// Delegate to observer pattern, set exit conditions on BaseCharacter.
	FExitConfig exitEvent;

protected:
	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey1;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey2;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey3;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey4;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey5;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonKey6;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonDoorKnob;

	// Button the player that the object can be picked.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* buttonExit;

	// Stores all the keys the player has.
	TArray<FName> playerKeys;
	// Stores all the availabre keys by quantity of keys the player has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys", meta = (AllowPrivateAccess))
	TArray<bool>availableKeys;

	// Door key selected by player, via buttons.
	FName selectedKey;

	// Necesary key selected to open the door.
	FName correctKey;
	// Bool open status holder.
	bool bIsOpen;

	// Color Value on hovered event.
	UPROPERTY(EditAnywhere, Category = "Button Colors", meta = (AllowPrivateAccess))
	FLinearColor hoveredColor = FLinearColor(0.0f, 0.0f, 0.0f);
	
	// Color Value on pressed event.
	UPROPERTY(EditAnywhere, Category = "Button Colors", meta = (AllowPrivateAccess))
	FLinearColor pressedColor = FLinearColor(0.0f, 0.0f, 0.0f);

	// Set the initial configuration of the buttons.
	void SetKeyButtons();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key1Pressed();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key2Pressed();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key3Pressed();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key4Pressed();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key5Pressed();

	// Manages when respective button key is pressed.
	UFUNCTION()
	void Key6Pressed();

	// Checks if the index is available and manage the selection of the correct key.
	void HadleKeyPressed(int keyIndex);

	// Manages when respective button key is pressed, open the door mechanic.
	UFUNCTION()
	void DoorKnobPressed();

	// Manages when respective button key is pressed, exits.
	UFUNCTION()
	void ExitPressed();
	
};
