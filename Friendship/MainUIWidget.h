// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseCharacter.h" // For MainUIWdget to have EInputControllerType
#include "MainUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class FRIENDSHIP_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public: 
	// Method to control Bar and text indicator, helps the player know the quantity of anxiety while playing.
	void UpdateAnxiety(float value);
	// Set the opacity, this depends if character is sprinting ot not.
	void SetAnxietyBarOpacity(float opacity);

	// Set the opacity, this depends if character is aiming or not.
	void SetCrossHairOpacity(float opacity);
	// Method to change color of CrossHair, this depends on what kind of actor is the player looking at.
	void SetCrossHairColor(FLinearColor color);

	// Method to control content of text, this depends on the type of controller the player.
	void SetTextContentByController(EInputControllerType controllerType);
	// Method to control text, indicate the player that the object can be picked.
	void SetInteractText(float opacity);

	// Method to control Bar and text indicator, helps the player know the quantity of flashlight while playing.
	void UpdateFlashlight(float value);
	// Set the opacity, this depends if character is using flashlight or not.
	void SetFlashlightBarOpacity(float opacity);

	// Method to control text, indicate the player an event that is happening in the gameplay.
	void SetDialogText(float opacity, FString dialog);

private:
	////////////////////////////////////////////// PROPERTIES SECTION //////////////////////////////////////////////
	// This section contains properties related to widget mechanics.

	// Bar and text indicator, helps the player know the quanity of anxiety while playing.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* anxietyBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* relaxedText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* anxietyText;

	// Text to indicate the player that the object can be picked.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* interacText;

	// Helps the player know where he's pointing at.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* crossHair;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* flashlightBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* dialogText;

};
