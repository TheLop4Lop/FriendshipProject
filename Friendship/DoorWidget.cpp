// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWidget.h"
#include "Components/Button.h"

// Class constructor.
void UDoorWidget::NativeConstruct()
{
    SetKeyButtons();
    availableKeys.Init(false, 6);

}

// Sets all the keys the player has.
void UDoorWidget::SetKeysForDoorKnob(TArray<FName>& keyTags, FName currentDoor)
{
    correctKey = currentDoor;

    for(FName singleKey : keyTags)
    {
        playerKeys.Add(singleKey);
    }

    for(int i = 0; i < playerKeys.Num(); i++)
    {
        availableKeys[i] = true;
    }

}

// Set the initial configuration of the buttons.
void UDoorWidget::SetKeyButtons()
{
    if(buttonKey1)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key1Pressed);
    }

    if(buttonKey2)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key2Pressed);
    }

    if(buttonKey3)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key3Pressed);
    }

    if(buttonKey4)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key4Pressed);
    }

    if(buttonKey5)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key5Pressed);
    }

    if(buttonKey6)
    {
        buttonKey1->OnClicked.AddDynamic(this, &UDoorWidget::Key6Pressed);
    }

    if(buttonDoorKnob)
    {
        buttonDoorKnob->OnClicked.AddDynamic(this, &UDoorWidget::DoorKnobPressed);
    }

    if(buttonExit)
    {
        buttonExit->OnClicked.AddDynamic(this, &UDoorWidget::ExitPressed);
    }

}

// Manages when respective button key is pressed;
void UDoorWidget::Key1Pressed()
{
    HadleKeyPressed(0);

}

// Manages when respective button key is pressed;
void UDoorWidget::Key2Pressed()
{
    HadleKeyPressed(1);

}

// Manages when respective button key is pressed;
void UDoorWidget::Key3Pressed()
{
    HadleKeyPressed(2);

}

// Manages when respective button key is pressed;
void UDoorWidget::Key4Pressed()
{
    HadleKeyPressed(3);

}

// Manages when respective button key is pressed;
void UDoorWidget::Key5Pressed()
{
    HadleKeyPressed(4);

}

// Manages when respective button key is pressed;
void UDoorWidget::Key6Pressed()
{
    HadleKeyPressed(5);

}

// Checks if the index is available and manage the selection of the correct key.
void UDoorWidget::HadleKeyPressed(int keyIndex)
{
    if(playerKeys.Num() > keyIndex)
    {
        selectedKey = playerKeys[keyIndex];
    }

}

// Manages when respective button key is pressed;
void UDoorWidget::DoorKnobPressed()
{   
    if(selectedKey.IsEqual(correctKey))
    {
        //PlayAnimation()
        bIsOpen = true;
        knobEvent.ExecuteIfBound();
    }

}

void UDoorWidget::ExitPressed()
{
    exitEvent.ExecuteIfBound();

}

bool UDoorWidget::CanOpenDoor()
{
    return bIsOpen;

}
