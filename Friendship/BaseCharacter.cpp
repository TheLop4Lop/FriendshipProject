// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "BaseCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.h"
#include "TakeableKey.h"
#include "BaseDoor.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    characterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
    characterCamera->SetupAttachment(GetMesh());

    lantern = CreateDefaultSubobject<USpotLightComponent>(TEXT("Character Lantern"));
    lantern->SetupAttachment(characterCamera);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    characterController = Cast<ABaseCharacterController>(GetController());

	ProportionalAnxietyHandle(maxStaminaByAnxiety);
	movementFunction1 = &ABaseCharacter::MoveForward;
    movementFunction2 = &ABaseCharacter::MoveRigth;

    lookFunction1 = &ABaseCharacter::LookUp;
    lookFunction2 = &ABaseCharacter::TurnRight;

    lookFunction3 = &ABaseCharacter::LookUpController;
    lookFunction4 = &ABaseCharacter::TurnRightController;

    SetWidgetInteractionClass();
    SetLanternIntensity(ZeroVal);
    canRelax = true;

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetGetActorToInteractInTheWorldWidget();
    SetCameraActionMovement();

    SetReduceAnxiety();
    SetHeartSound();

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(PlayerInputComponent)
	{
        InputComponent->BindAction(TEXT("KEYBOARD"), EInputEvent::IE_Pressed, this, &ABaseCharacter::SetUsingKeyBoard);
        InputComponent->BindAxis(TEXT("GAMEPAD"), this, &ABaseCharacter::SetUsingController);

		InputComponent->BindAxis(TEXT("WKey"), this, &ABaseCharacter::HandleMovementInputAxis1); 
        InputComponent->BindAxis(TEXT("RKey"), this, &ABaseCharacter::HandleMovementInputAxis2);

        InputComponent->BindAxis(TEXT("YAxis"), this, &ABaseCharacter::HandleLookInputAxis1); 
        InputComponent->BindAxis(TEXT("XAxis"), this, &ABaseCharacter::HandleLookInputAxis2);

        InputComponent->BindAxis(TEXT("YAxisController"), this, &ABaseCharacter::HandleLookInputAxis1); 
        InputComponent->BindAxis(TEXT("XAxisController"), this, &ABaseCharacter::HandleLookInputAxis2);

        InputComponent->BindAction(TEXT("Swap"), EInputEvent::IE_Pressed, this, &ABaseCharacter::SwapMovement);

        InputComponent->BindAction(TEXT("SprintKey"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Sprint);
        InputComponent->BindAction(TEXT("SprintKey"), EInputEvent::IE_Released, this, &ABaseCharacter::Walk);

        InputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Aim);
        InputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &ABaseCharacter::StopAim);
        InputComponent->BindAction(TEXT("ThrowProjectile"), EInputEvent::IE_Pressed, this, &ABaseCharacter::ThrowProjectile);
        InputComponent->BindAction(TEXT("Lantern"), EInputEvent::IE_Pressed, this, &ABaseCharacter::LanternON);
        InputComponent->BindAction(TEXT("Lantern"), EInputEvent::IE_Released, this, &ABaseCharacter::LanternOFF);

        InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ABaseCharacter::TakeObject);
        InputComponent->BindAction(TEXT("Recharge"), EInputEvent::IE_Pressed, this, &ABaseCharacter::NewBatteryOnFlashlight);
	}

}

////////////////////////////////////////////// WIDGET SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character's Widget.

// Method that implements Widget Class.
void ABaseCharacter::SetWidgetInteractionClass()
{
    if(characterController && mainWidgetClass)
    {
        mainWidget = Cast<UMainUIWidget>(CreateWidget(characterController, mainWidgetClass));
        if(mainWidget)
        {
            mainWidget->AddToViewport();
        } 
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("NULL value on characterController or mainWidgetClass."));
    }

}

////////////////////////////////////////////// MOVEMENT SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character movement and control.

// Method that manage the spring mechanic.
void ABaseCharacter::Sprint()
{
    if(GetCharacterMovement()->Velocity.SizeSquared() > ZeroVal)
    {
        GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(SprintSpeed, WalkSpeed, GetWorld()->DeltaTimeSeconds, InterpMin);
        isSprinting = true;

        GetWorldTimerManager().ClearTimer(timeHandle);
        GetWorldTimerManager().SetTimer(timeHandle, this, &ABaseCharacter::IncreaseAnxiety, anxietyPeriod, isSprinting);
    }

}

// Method that manage the walk mechanic.
void ABaseCharacter::Walk() 
{
    if(anxietyLevel != ZeroVal)
    {
        GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(WalkSpeed, SprintSpeed, GetWorld()->DeltaTimeSeconds, InterpMax);
        isSprinting = false;
        doOnceRelax = true;
    }
	
}

//Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
void ABaseCharacter::HandleMovementInputAxis1(float value)
{
    if(movementFunction1 != nullptr)
    {
        (this->*movementFunction1)(value);
    }

}

//Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
void ABaseCharacter::HandleMovementInputAxis2(float value)
{
    if(movementFunction2 != nullptr)
    {
        (this->*movementFunction2)(value);
    }

}

// Movement Forward method.
void ABaseCharacter::MoveForward(float value)
{
    AddMovementInput(GetActorForwardVector(), value);

}

// Movement Right method.
void ABaseCharacter::MoveRigth(float value)
{
    AddMovementInput(GetActorRightVector(), value);

}

// Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
void ABaseCharacter::HandleLookInputAxis1(float value)
{
    if(lookFunction1 != nullptr)
    {
        (this->*lookFunction1)(value);
    }

}

// Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
void ABaseCharacter::HandleLookInputAxis2(float value)
{
    if(lookFunction2 != nullptr)
    {
        (this->*lookFunction2)(value);
    }

}

// Look up Method.
void ABaseCharacter::LookUp(float value)
{
    AddControllerPitchInput(value);

}

// Turn Method.
void ABaseCharacter::TurnRight(float value)
{
	AddControllerYawInput(value);

}

// Look up Method. ON CONTROLLER
void ABaseCharacter::LookUpController(float value)
{
    AddControllerPitchInput(value * (yAxisRate * GetWorld()->GetDeltaSeconds()));

}

// Turn Method. ON CONTROLLER
void ABaseCharacter::TurnRightController(float value)
{
	AddControllerYawInput(value * (xAxisRate * GetWorld()->GetDeltaSeconds()));

}

// Methods used to define keyboard controller. (This can be unimplemented)
void ABaseCharacter::SetUsingKeyBoard()
{
    controllerType = EInputControllerType::KEYBOARD_CONTROLLER;

}

// Methods used to define gamepad controller. (This can be unimplemented)
void ABaseCharacter::SetUsingController(float value)
{
    float minControllerRatio = 0.1f;
    if(value > minControllerRatio)
    {
        controllerType = EInputControllerType::CONTROLLER_CONTROLLER;
    }

}

// Called when Max Anxiety is reached, it change the controller inputs.
void ABaseCharacter::SwapMovement()
{
    if(!controlSwap)
    {
        movementFunction1 = &ABaseCharacter::MoveRigth; 
        movementFunction2 = &ABaseCharacter::MoveForward;

        lookFunction1 = &ABaseCharacter::TurnRight;
        lookFunction2 = &ABaseCharacter::LookUp;

        lookFunction3 = &ABaseCharacter::TurnRightController;
        lookFunction4 = &ABaseCharacter::LookUpController;
    }else{
        movementFunction1 = &ABaseCharacter::MoveForward;
        movementFunction2 = &ABaseCharacter::MoveRigth;

        lookFunction1 = &ABaseCharacter::LookUp;
        lookFunction2 = &ABaseCharacter::TurnRight;

        lookFunction3 = &ABaseCharacter::LookUpController;
        lookFunction4 = &ABaseCharacter::TurnRightController;
    }

    controlSwap = !controlSwap;

}

// Sets Camera animation by movement.
void ABaseCharacter::SetCameraActionMovement()
{
    if(characterController)
    {
        if(GetCharacterMovement()->Velocity.Size() < WalkSpeed/2)
        {
            characterController->SetCamerastateMovement(ECameraMovement::IDLE);
        }else if(GetCharacterMovement()->Velocity.Size() < SprintSpeed - MaxAnxiety && GetCharacterMovement()->Velocity.Size() >= WalkSpeed/2)
        {
            characterController->SetCamerastateMovement(ECameraMovement::WALKING);
            if(stepsSound && doOnceStep)
            {
                GetWorldTimerManager().SetTimer(timeStep, this, &ABaseCharacter::stepiStp, 0.40f, doOnceStep);
                
                doOnceStep = false;
            }
        }else if(isSprinting || anxietyLevel > MaxAnxiety/2)
        {
            characterController->SetCamerastateMovement(ECameraMovement::SPRINTING);
        }
    }

}

// Test function for steps functionality.
void ABaseCharacter::stepiStp()
{
    UGameplayStatics::PlaySoundAtLocation(this, stepsSound, GetActorLocation());
    doOnceStep = true;

}

////////////////////////////////////////////// ANXIETY SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character anxiety mechanic.

// Methods than control the characters Anxiety
void ABaseCharacter::IncreaseAnxiety()
{
    if(anxietyLevel < MaxAnxiety)
    {
        anxietyLevel += anxietyAmount;
        if(mainWidget)
        {
            float opacityBar = 1.0f;
            mainWidget->UpdateAnxiety(anxietyLevel/MaxAnxiety);
            mainWidget->SetAnxietyBarOpacity(opacityBar);
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
        }
    }else if(anxietyLevel >= MaxAnxiety)
    {
        anxietyLevel = MaxAnxiety;
    }

}

// Sets initial conditions to manage the reduction on anxiety.
void ABaseCharacter::SetReduceAnxiety()
{
    if(anxietyLevel != ZeroVal && !isSprinting && canRelax && doOnceRelax) // in a fuucntion
    {
        GetWorldTimerManager().ClearTimer(timeHandle);
        GetWorldTimerManager().SetTimer(timeHandle, this, &ABaseCharacter::ReduceAnxiety, anxietyPeriod, anxietyLevel != ZeroVal);

        doOnceRelax = false;
    }

}

// Methods than manage the anxiety reduction value.
void ABaseCharacter::ReduceAnxiety()
{
    if(anxietyLevel > ZeroVal)
    {
        anxietyLevel -= anxietyAmount;
        if(mainWidget)
        {
            mainWidget->UpdateAnxiety(anxietyLevel/MaxAnxiety);
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
        }
    }else if(anxietyLevel <= ZeroVal)
    {
        anxietyLevel = ZeroVal;
        if(mainWidget)
        {
            mainWidget->SetAnxietyBarOpacity(ZeroVal);
        }
    }

}

// Method that modify the quantity of MAX ansiety, this change with Darkness or another anxiety mechanic.
void ABaseCharacter::ProportionalAnxietyHandle(float newStamina)
{
    float scalingFactor = maxStaminaByAnxiety/newStamina;
    anxietyPeriod = maxAnxietyPeriod/scalingFactor;
    anxietyAmount = ((anxietyPeriod * MaxAnxiety)/newStamina);

}

// Methods that handle in public increace and decreace anxiety on TriggerLuminare Class.
void ABaseCharacter::IncreaseAnxietyOnCharacter()
{
    GetWorldTimerManager().ClearTimer(timeHandle);
    IncreaseAnxiety();

}

// Change boolean condition values to access relax mechanic.
void ABaseCharacter::SetConditionsToRelax(bool relax)
{
    canRelax = relax;
    doOnceRelax = canRelax;

}

// Returns the current anxiety period.
float ABaseCharacter::GetAnxietyPeriod()
{
    return anxietyPeriod;

}

// Returns the current anxiety level.
float ABaseCharacter::GetAnxietyLevel()
{
    return anxietyLevel;

}

// Returns wether or not the player is sprinting.
bool ABaseCharacter::isCharacterSptinting()
{
    return isSprinting;

}

// Sets initial condition to call heartbeat.
void ABaseCharacter::SetHeartSound()
{
    if(anxietyLevel != ZeroVal && doOnceHeart)
    {
        float minHeartValue = 1.0f;
        float heartBPM = FMath::Clamp(this->heartSound->GetDuration()/((anxietyLevel/MaxAnxiety) * this->heartSound->GetDuration()), 
                                        minHeartValue, this->heartSound->GetDuration());
        
        GetWorldTimerManager().ClearTimer(timeHeart);
        GetWorldTimerManager().SetTimer(timeHeart, this, &ABaseCharacter::CheckAndPlayHeartSound, heartBPM, doOnceHeart);

        doOnceHeart = false;
    }

}

// Plays Heartbeat sound.
void ABaseCharacter::CheckAndPlayHeartSound()
{
    if(heartSound)
    {
        float minHeartValue = 1.0f;
        float heartVolume = anxietyLevel/MaxAnxiety;
        float heartPitch = FMath::Clamp(((anxietyLevel/MaxAnxiety) * this->heartSound->GetDuration()), minHeartValue, this->heartSound->GetDuration());

        UGameplayStatics::PlaySoundAtLocation(this, heartSound, GetActorLocation(), heartVolume, heartPitch);

        doOnceHeart = true;
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Sound to play for heartSound!"));
    }

}

////////////////////////////////////////////// INTERACTION SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character interaction mechanic.

// Methods that manage the conditons to aim, this calls a Widget and determine conditions to damage actors.
void ABaseCharacter::Aim()
{
    isAiming = true;
    if(mainWidget)
    {
        mainWidget->SetCrossHairOpacity(1.0f);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
    }

}

// Stops aiming an removes the wigdet.
void ABaseCharacter::StopAim()
{
    isAiming = false;
    if(mainWidget)
    {
        mainWidget->SetCrossHairOpacity(ZeroVal);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
    }

}

// Generate linetrace collision to object (May be updated to spawn object).
void ABaseCharacter::ThrowProjectile()
{
    if(isAiming)
    {
        float damageIn = 2.0; //This may change after implementing throable class.
        if(actorInSight)
        {
            if(actorInSight && actorInSight->ActorHasTag(TagDestroyableActor))
            {
                FPointDamageEvent DamageEven(damageIn, Hit, actorInSight->GetActorLocation(), nullptr);
                actorInSight->TakeDamage(damageIn, DamageEven, characterController, this);
            }
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("actorInSight has a NULL value."));
        }
    }

}

// Set GetActorToInteractInTheWorld function.
void ABaseCharacter::SetGetActorToInteractInTheWorldWidget()
{
    if(mainWidget)
    {  
        GetActorToInteractInTheWorld();
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("mainWidget is a NULL value, checkk Character Blueprint"));
    }

}

// Get the actor on player sight, this adds interaction on widget, depends of the type of object.
void ABaseCharacter::GetActorToInteractInTheWorld()
{
    pickableActor = Cast<ABaseTakeable>(ActorTargetByLineTrace(Hit, pickRange));
    currentDoor = Cast<ABaseDoor>(ActorTargetByLineTrace(Hit, pickRange));
    if(pickableActor && pickableActor->ActorHasTag(TagTakeableActor) || currentDoor && !currentDoor->IsDoorOpen())
    {
        float opacityText = 1.0f;
        mainWidget->SetTextContentByController(controllerType);
        mainWidget->SetInteractText(opacityText);
    }else
    {
        mainWidget->SetInteractText(ZeroVal);
    }

    if(isAiming && ActorTargetByLineTrace(Hit, throwRange))
    {
        actorInSight = ActorTargetByLineTrace(Hit, throwRange);
        if(actorInSight && actorInSight->ActorHasTag(TagDestroyableActor))
        {
            mainWidget->SetCrossHairColor(FLinearColor::Red);
        }else if(actorInSight->ActorHasTag(TagTakeableActor))
        {
            mainWidget->SetCrossHairColor(FLinearColor::Green);
        }
    }else
    {
        mainWidget->SetCrossHairColor(FLinearColor::White);
    }

}

// Method that return and interact with the actors in the world.
AActor* ABaseCharacter::ActorTargetByLineTrace(FHitResult& result, float& range)
{
    FVector throwLocation;
    FRotator throwRotation;
    FVector throwEnd;
    
    if(characterController)
    {
        characterController->GetPlayerViewPoint(throwLocation, throwRotation);
        throwEnd = throwLocation + (throwRotation.Vector() * range);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("NULL value on characterController."));
    }

    float sphereRadius = 1.0f;
    FCollisionShape sphere = FCollisionShape::MakeSphere(sphereRadius);
    FCollisionQueryParams params;
    params.AddIgnoredActor(this);

    if(GetWorld()->LineTraceSingleByChannel(result, throwLocation, throwEnd, ECollisionChannel::ECC_GameTraceChannel1, params))
    {
        return result.GetActor();
    }

    return nullptr;

}

// Method that interct with BaseTakeable class, add value into players inventory variables, this depends on the Takeable enum.
void ABaseCharacter::TakeObject()
{
    if(pickableActor)
    {
        takeableType = pickableActor->GetTypeOfTakeable();
        ATakeableKey* key = Cast<ATakeableKey>(pickableActor);
        switch (takeableType)
        {
            case ETakeableType::KEY:
            if(key)
            {
                keyQuantity += key->GetQuanityOfTakeable();
                keyTags.Add(key->GetKeyNameUnlockDoor());
            }
            break;

            case ETakeableType::BATTERY:
            batteryQuantity += pickableActor->GetQuanityOfTakeable();
            break;

            case ETakeableType::THROWABLE:
            thowableQuantity += pickableActor->GetQuanityOfTakeable();
            break;
        
        default:
            break;
        }

        pickableActor->DestroyTakeable();
    }else if(currentDoor)
    {
       currentDoor->TryAccessToDoor(this);
    }else
    {
         UE_LOG(LogTemp, Warning, TEXT("No Actor to interact in sight."));
    }

}

// Calls mainWidget to add a dialog, depends on world interaction or mechanic.
void ABaseCharacter::SituationDialog(FString dialog)
{
    if(mainWidget)
    {
        float opacityText = 1.0f;
        mainWidget->SetDialogText(opacityText, dialog);
        FTimerDelegate dialogTimer;
        dialogTimer.BindLambda([this]() 
        {
            mainWidget->SetDialogText(ZeroVal, "");
        });
        
        GetWorldTimerManager().SetTimer(timeFlashLightRecharge, dialogTimer, dialogDuration, false);
    }

}

////////////////////////////////////////////// INVENTORY SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character inventory.

// Method that handles keys inventory, checks if player has the correct key.
bool ABaseCharacter::HasKeyToOpenDoor(FName door)
{
    for(FName singleKey : keyTags)
    {
        if(singleKey.IsEqual(door))
        {
            return true;
        }
    }
    return false;

}

////////////////////////////////////////////// LANTERN SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character lantern mechanic.

// Turn ON flashlight.
void ABaseCharacter::LanternON()
{
    if(!isAiming)
    {
        isLanternOn = true;
        SetLanternIntensity(lanternIntensity);
        GetWorldTimerManager().SetTimer(timeHandleFlashLight, this, &ABaseCharacter::UseLanternBattery, 0.0625f, isLanternOn);
    }

}

// Turn OFF flashlight.
void ABaseCharacter::LanternOFF()
{
    isLanternOn = false;
    SetLanternIntensity(ZeroVal);
    GetWorldTimerManager().ClearTimer(timeHandleFlashLight);

    if(mainWidget)
    {
        mainWidget->SetFlashlightBarOpacity(ZeroVal);
    }

}

// Set initial light intensity.
void ABaseCharacter::SetLanternIntensity(float intensity)
{
    if(lantern)
    {
        lantern->SetIntensity(intensity);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Lanter class to interact."));
    }

}

// Method that manage lantern's battery
void ABaseCharacter::UseLanternBattery()
{
    currentBatteryAmount -= batteryWearAmount;
    if(mainWidget)
    {
        float opacityBar = 1.0f;
        mainWidget->SetFlashlightBarOpacity(opacityBar);
        mainWidget->UpdateFlashlight(currentBatteryAmount/maxBatteryAmount);

        if(currentBatteryAmount <= ZeroVal)
        {
            LanternOFF();
            currentBatteryAmount = ZeroVal;
            mainWidget->SetFlashlightBarOpacity(ZeroVal);
        }
    }

}

// Method that manage recharge battery logic.
void ABaseCharacter::NewBatteryOnFlashlight()
{
    LanternOFF();
    if(!isLanternOn && batteryQuantity > ZeroVal && currentBatteryAmount == ZeroVal)
    {
        FTimerDelegate rechargeTimer;
        rechargeTimer.BindLambda([this](){
            currentBatteryAmount = FMath::RandRange((maxBatteryAmount/2), maxBatteryAmount);
        });
        GetWorldTimerManager().SetTimer(timeFlashLightRecharge, rechargeTimer, rechargeDelay, false);

        return;
    }
    
    FString dialog;
    (batteryQuantity > ZeroVal && currentBatteryAmount != ZeroVal) ? dialog = "I still have some battery left." : dialog = "I don't have another battery.";
    SituationDialog(dialog);

}
