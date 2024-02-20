// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "BaseCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.h"

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

	ProportionalAnxietyHandle(staminaByAnxiety);
	movementFunction1 = &ABaseCharacter::MoveForward;
    movementFunction2 = &ABaseCharacter::MoveRigth;

    lookFunction1 = &ABaseCharacter::LookUp;
    lookFunction2 = &ABaseCharacter::TurnRight;

    lookFunction3 = &ABaseCharacter::LookUpController;
    lookFunction4 = &ABaseCharacter::TurnRightController;

    SetWidgetInteractionClass();
    SetLanternIntensity(Zero);

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(mainWidget)
    {  
        GetActorToInteractInTheWorld();
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("mainWidget is a NULL value, checkk Character Blueprint"));
    }

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(PlayerInputComponent)
	{
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
	}

}

////////////////////////////////////////////// WIDGET SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character's Widget.
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

//Methods that control the speed in of the character movement.
void ABaseCharacter::Sprint()
{
    GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(SprintSpeed, WalkSpeed, GetWorld()->DeltaTimeSeconds, InterpMin);
    isSprinting = true;
    GetWorldTimerManager().SetTimer(timeHandle, this, &ABaseCharacter::IncreaseAnxiety, anxietyPeriod, isSprinting);
	
}

void ABaseCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(WalkSpeed, SprintSpeed, GetWorld()->DeltaTimeSeconds, InterpMax);
    isSprinting = false;
    GetWorldTimerManager().SetTimer(timeHandle, this, &ABaseCharacter::ReduceAnxiety, anxietyPeriod, !isSprinting);

}

//Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
void ABaseCharacter::HandleMovementInputAxis1(float value)
{
    if(movementFunction1 != nullptr)
    {
        (this->*movementFunction1)(value);
    }

}

void ABaseCharacter::HandleMovementInputAxis2(float value)
{
    if(movementFunction2 != nullptr)
    {
        (this->*movementFunction2)(value);
    }

}

//Movement methods.
void ABaseCharacter::MoveForward(float value)
{
    AddMovementInput(GetActorForwardVector(), value);

}

void ABaseCharacter::MoveRigth(float value)
{
    AddMovementInput(GetActorRightVector(), value);

}

//Methods that controll the look and turn, this movement depens on the function pointer.
void ABaseCharacter::HandleLookInputAxis1(float value)
{
    if(lookFunction1 != nullptr)
    {
        (this->*lookFunction1)(value);
    }

}

void ABaseCharacter::HandleLookInputAxis2(float value)
{
    if(lookFunction2 != nullptr)
    {
        (this->*lookFunction2)(value);
    }

}

//Look and turn methods.
void ABaseCharacter::LookUp(float value)
{
    AddControllerPitchInput(value);

}

void ABaseCharacter::TurnRight(float value)
{
	AddControllerYawInput(value);

}

//Look and turn methods. ON CONTROLLER
void ABaseCharacter::LookUpController(float value)
{
    AddControllerPitchInput(value * (yAxisRate * GetWorld()->GetDeltaSeconds()));

}

void ABaseCharacter::TurnRightController(float value)
{
	AddControllerYawInput(value * (xAxisRate * GetWorld()->GetDeltaSeconds()));

}

//Called when Max Anxiety is reached, it change the controller inputs.
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

////////////////////////////////////////////// ANXIETY SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character anxiety mechanic.

// Methods than control the characters Anxiety
void ABaseCharacter::IncreaseAnxiety()
{
    if(!(GetCharacterMovement()->Velocity.SizeSquared() > 0)) return;

    if(anxietyLevel < MaxAnsiety)
    {
        anxietyLevel += anxietyAmount;
        if(mainWidget)
        {
            mainWidget->UpdateAnxiety(anxietyLevel/MaxAnsiety);
            mainWidget->SetAnxietyBarOpacity(1.0f);
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
        }
    }else if(anxietyLevel >= MaxAnsiety)
    {
        anxietyLevel = MaxAnsiety;
    }

}

void ABaseCharacter::ReduceAnxiety()
{
    if(anxietyLevel == Zero) return; 

    if(anxietyLevel > Zero)
    {
        anxietyLevel -= anxietyAmount;
        if(mainWidget)
        {
            mainWidget->UpdateAnxiety(anxietyLevel/MaxAnsiety);
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
        }
    }else if(anxietyLevel <= Zero)
    {
        anxietyLevel = Zero;
        if(mainWidget)
        {
            mainWidget->SetAnxietyBarOpacity(Zero);
        }
    }

}

// Method that modify the quantity of MAX ansiety, this change with Darkness or another anxiety mechanic.
void ABaseCharacter::ProportionalAnxietyHandle(float newStamina)
{
    float scalingFactor = maxStaminaByAnxiety/newStamina;
    anxietyPeriod = maxAnxietyPeriod/scalingFactor;
    anxietyAmount = ((anxietyPeriod * 100.0f)/newStamina);

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

void ABaseCharacter::StopAim()
{
    isAiming = false;
    if(mainWidget)
    {
        mainWidget->SetCrossHairOpacity(Zero);
    }else
    {
        UE_LOG(LogTemp, Warning, TEXT("NULL value on mainWidgetClass."));
    }

}

void ABaseCharacter::ThrowProjectile()
{
    if(isAiming)
    {
        if(actorInSight)
        {
            if(actorInSight && actorInSight->ActorHasTag(TagDestroyableActor))
            {
                FPointDamageEvent DamageEven(2.0, Hit, actorInSight->GetActorLocation(), nullptr);
                actorInSight->TakeDamage(2.0, DamageEven, characterController, this);
                UE_LOG(LogTemp, Display, TEXT("HAAY ME DUELE"));
            }
        }else
        {
            UE_LOG(LogTemp, Warning, TEXT("actorInSight has a NULL value."));
        }
    }

}

// Method that change the properties of mainWidget, this to detemine the type of actor, if it can be destroyed or be picked.
void ABaseCharacter::GetActorToInteractInTheWorld()
{
    pickableActor = ActorTargetByLineTrace(Hit, pickRange);
    if(pickableActor && pickableActor->ActorHasTag(TagPickableActor))
    {
        mainWidget->SetInteractText(1.0f);
    }else
    {
        mainWidget->SetInteractText(Zero);
    }

    if(isAiming && ActorTargetByLineTrace(Hit, throwRange))
    {
        actorInSight = ActorTargetByLineTrace(Hit, throwRange);
        if(actorInSight && actorInSight->ActorHasTag(TagDestroyableActor))
        {
            mainWidget->SetCrossHairColor(FLinearColor::Red);
        }else if(actorInSight->ActorHasTag(TagPickableActor))
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

    FCollisionShape sphere = FCollisionShape::MakeSphere(0.5f);
    FCollisionQueryParams params;
    params.AddIgnoredActor(this);

    if(GetWorld()->LineTraceSingleByChannel(result, throwLocation, throwEnd, ECollisionChannel::ECC_GameTraceChannel1, params))
    {
        return result.GetActor();
    }

    return nullptr;

}

////////////////////////////////////////////// LANTERN SECTION //////////////////////////////////////////////
// This section contains properties and methods related to character lantern mechanic.

// Methods that manage the lantern state.
void ABaseCharacter::LanternON()
{
    if(!isAiming)
    {
        SetLanternIntensity(lanternIntensity);
    }

}

void ABaseCharacter::LanternOFF()
{
    SetLanternIntensity(Zero);

}

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
