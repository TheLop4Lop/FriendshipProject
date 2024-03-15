// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

//Class constructor.
void UMainUIWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(anxietyBar && crossHair && interacText)
    {
        SetFlashlightBarOpacity(Zero);
        anxietyBar->SetPercent(Zero);
        SetAnxietyNoiseOpacity(Zero);
        SetAnxietyBarOpacity(Zero);
        SetCrossHairOpacity(Zero);
        SetDialogText(Zero, "");
        SetInteractText(Zero);
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No anxietyBar found in WidgetBlueprint"));
    }

}

// Method to control Bar and text indicator, helps the player know the quanity of anxiety while playing.
void UMainUIWidget::UpdateAnxiety(float value)
{
    if(anxietyBar && backBlur)
    {
        anxietyValue = FMath::Clamp(value, Zero, One);
        anxietyBar->SetPercent(anxietyValue);
        backBlur->SetBlurStrength(value * blurRate);
        if(value >= percentageBar)
        {
            float noiseClampedValue = FMath::Clamp(value, Zero, One);
            float adjustedOpacity = FMath::Max(noiseClampedValue - percentageBar, Zero) * opacityAjustment;
            SetAnxietyNoiseOpacity(adjustedOpacity);
        }
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No anxietyBar found in WidgetBlueprint"));
    }

}

// Set the opacity, this depends if character is sprinting ot not.
void UMainUIWidget::SetAnxietyBarOpacity(float opacity)
{
    if(anxietyBar && relaxedText && anxietyText)
    {
        anxietyBar->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
        relaxedText->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
        anxietyText->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No anxietyComponents found in WidgetBlueprint to update Opacity."));
    }

}

// Set the opacity, this depends if character is aiming ot not.
void UMainUIWidget::SetAnxietyNoiseOpacity(float opacity)
{
    if(anxietyNoise)
    {
        anxietyNoise->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No Anxiety Noise found in WidgetBlueprint to update Opacity."));
    }

}

// Set the opacity, this depends if character is aiming ot not.
void UMainUIWidget::SetCrossHairOpacity(float opacity)
{
    if(crossHair)
    {
        crossHair->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No crossHair found in WidgetBlueprint to update Opacity."));
    }

}

// Method to change color of CrossHair, this depends on what kind of actor is the player looking at.
void UMainUIWidget::SetCrossHairColor(FLinearColor color)
{
    if(crossHair)
    {
        crossHair->SetColorAndOpacity(color);
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No crossHair found in WidgetBlueprint to update Opacity."));
    }

}

// Method to control content of text, this depends on the type of controller the player.
void UMainUIWidget::SetTextContentByController(EInputControllerType controllerType, FString interaction)
{
    FString updateText;
    switch(controllerType)
    {
        case EInputControllerType::CONTROLLER_CONTROLLER:
            updateText = TEXT("Press 'X' to " + interaction);
            interacText->SetText(FText::FromString(updateText));
            break;
        
        case EInputControllerType::KEYBOARD_CONTROLLER:
            updateText = TEXT("Press 'E' to "  + interaction);
            interacText->SetText(FText::FromString(updateText));
            break;
    
        case EInputControllerType::OCULUS_CONTROLLER:
            updateText = TEXT("Grap to "  + interaction);
            interacText->SetText(FText::FromString(updateText));
            break;
        
        default:
            break;
    }
}

// Method to control text, indicate the player that the object can be picked.
void UMainUIWidget::SetInteractText(float opacity)
{
    interacText->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    
}

void UMainUIWidget::UpdateFlashlight(float value)
{
    if(flashlightBar)
    {
        float ClampedValue = FMath::Clamp(value, Zero, One);
        flashlightBar->SetPercent(ClampedValue);
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("No flashlightBar found in WidgetBlueprint"));
    }

}

// Method to control text, indicate the player an event that is happening in the gameplay.
void UMainUIWidget::SetFlashlightBarOpacity(float opacity)
{
    flashlightBar->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    flashlightIcon->SetRenderOpacity(opacity);

}

// Method to control text, indicate the player an event that is happening in the gameplay.
void UMainUIWidget::SetDialogText(float opacity, FString dialog)
{
    dialogText->SetRenderOpacity(FMath::FInterpTo(opacity, anxietyBar->RenderOpacity, GetWorld()->GetDeltaSeconds(), MinInterp));
    dialogText->SetText(FText::FromString(dialog));

}
