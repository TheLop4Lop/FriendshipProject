// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseCharacter.h" // For MainUIWdget to have EInputControllerType
#include "MainUIWidget.generated.h"

float const Zero = 0; // Zero value const.
float const One = 1; // One value const.
float const MinInterp = 0.01; // 0.01 value const.

UCLASS()
class FRIENDSHIP_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//Class constructor.
	virtual void NativeConstruct() override;

public: 
	// Method to control Bar and text indicator, helps the player know the quantity of anxiety while playing.
	void UpdateAnxiety(float value);
	// Set the opacity, this depends if character is sprinting ot not.
	void SetAnxietyBarOpacity(float opacity);
	void SetAnxietyNoiseOpacity(float opacity);

	// Set the opacity, this depends if character is aiming or not.
	void SetCrossHairOpacity(float opacity);
	// Method to change color of CrossHair, this depends on what kind of actor is the player looking at.
	void SetCrossHairColor(FLinearColor color);

	// Method to control content of text, this depends on the type of controller the player.
	void SetTextContentByController(EInputControllerType controllerType, FString interaction);
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

	// Bar indicator, helps the player know the quantity of anxiety while playing.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* anxietyBar;

	// Relax text indicator, helps the player know the quantity of anxiety while playing.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* relaxedText;

	// Anxiety text indicator, helps the player know the quantity of anxiety while playing.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* anxietyText;

	// Text to indicate the player that the object can be picked.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* interacText;

	// Helps the player know where he's pointing at.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* crossHair;

	// Bar indicator, helps the player know the quantity of battery while playing.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* flashlightBar;

	// Text to indicate the context on the situation.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* dialogText;

	// Add mechanic into gameplay mechanic, the blur strenght depends on the anxiety.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBackgroundBlur* backBlur;

	// Add mechanic into gameplay mechanic, the noise strenght depends on the anxiety.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* anxietyNoise;

	// Determine the general strenght on the blur.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anxiey Blur", meta = (AllowPrivateAccess))
	float blurRate = 3.5f;

	// Determine the general opacity on the blur.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anxiey Blur", meta = (AllowPrivateAccess))
	float opacityAjustment = 1.4f;

	// Value that determines when some action on the mechanics.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anxiey Blur", meta = (AllowPrivateAccess))
	float percentageBar = 0.25;
	
};
