// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseTakeable.h"
#include "BaseCharacter.generated.h"

// ENUM used to determine the controller of the player, this will change the interaction text on mainWidget.
UENUM(BlueprintType)
enum class EInputControllerType : uint8
{
	KEYBOARD_CONTROLLER,
	CONTROLLER_CONTROLLER,
	OCULUS_CONTROLLER
};

float const MaxAnsiety = 100; // Max anxiety value const.
float const Zero = 0; // Zero value const.
float const InterpMin = 0.3; // Interpolation minimum paramenter.
float const InterpMax = 0.5; // Interpolation maximum paramenter.

UCLASS()
class FRIENDSHIP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ENUM variable, keeps track of the controller, updated on players input.
	EInputControllerType controllerType;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when Max Anxiety is reached, it change the controller inputs.
	void SwapMovement();
	// Method that modify the quantity of MAX ansiety, this change with Darkness or another anxiety mechanic.
	void ProportionalAnxietyHandle(float newStamina);

private:
	class ABaseCharacterController* characterController;

	////////////////////////////////////////////// WIDGET SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character's Widget.
	UPROPERTY(EditAnywhere, Category = "Character Widget", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> mainWidgetClass;
	class UMainUIWidget* mainWidget;

	// Method that implements Widget Class.
	void SetWidgetInteractionClass(); 

	////////////////////////////////////////////// MOVEMENT SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character movement and control.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float WalkSpeed = 600.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float SprintSpeed = 900.0f;

	// Methods that control the speed in of the character movement.
	void Sprint();
	void Walk();
	
	// Funtion pointer, this pointer change its value  on character movement when Max Anxiety is reached.
	void (ABaseCharacter::*movementFunction1)(float) = nullptr;
	void (ABaseCharacter::*movementFunction2)(float) = nullptr;

	// Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
	void HandleMovementInputAxis1(float value);
	void HandleMovementInputAxis2(float value);

	// Movement methods.
	void MoveForward(float value);
	void MoveRigth(float value);

	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached.
	void (ABaseCharacter::*lookFunction1)(float) = nullptr;
	void (ABaseCharacter::*lookFunction2)(float) = nullptr;

	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached. ON CONTROLLER
	void (ABaseCharacter::*lookFunction3)(float) = nullptr;
	void (ABaseCharacter::*lookFunction4)(float) = nullptr;

	// Methods that controll the look and turn, this movement depens on the function pointer.
	void HandleLookInputAxis1(float value);
	void HandleLookInputAxis2(float value);

	// Look and turn methods.
	void LookUp(float value);
	void TurnRight(float value);

	// Look and turn methods. ON CONTROLLER
	void LookUpController(float value);
	void TurnRightController(float value);
	float yAxisRate = 5;
	float xAxisRate = 5;

	// Methods used to define what kind of controller the player is usign.
	void SetUsingKeyBoard();
	void SetUsingController(float value);

	// Control Swap state.
	bool controlSwap = false;

	////////////////////////////////////////////// ANXIETY SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character anxiety mechanic.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float maxStaminaByAnxiety = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float staminaByAnxiety = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float maxAnxietyPeriod = 0.0625f;

	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyPeriod;

	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyAmount;

	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyLevel;

	// Methods than control the characters Anxiety
	void IncreaseAnxiety();
	void ReduceAnxiety();

	// Movement Control bools, this controls if anxiety is triggered by sprinting.
	bool isMoving = false;
	bool isSprinting;

	FTimerHandle timeHandle;

	////////////////////////////////////////////// INTERACTION SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character interaction mechanic.
	UPROPERTY(EditAnywhere, Category = "Character Throw", meta = (AllowPrivateAccess))
	float throwRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Character Pick", meta = (AllowPrivateAccess))
	float pickRange = 80.0f;

	// Methods that manage the conditons to aim, this calls a Widget and determine conditions to damage actors.
	void Aim();
	void StopAim();
	void ThrowProjectile();

	// Method that change the properties of mainWidget, this to detemine the type of actor, if it can be destroyed or be picked.
	void GetActorToInteractInTheWorld();
	// Method that return and interact with the actors in the world.
	AActor* ActorTargetByLineTrace(FHitResult& result, float& range);
	AActor* actorInSight;

	// Method that interct with BaseTakeable class, add value into players inventory variables, this depends on the Takeable enum.
	void TakeObject();
	ABaseTakeable* pickableActor;
	
	FHitResult Hit;
	
	// Variables of controll, determine the kind of interanction of an actor in the world.
	FName TagDestroyableActor = FName("Destroy");
	FName TagTakeableActor = FName("Takeable");

	// Control variable, keeps track of aiming state.
	bool isAiming;

	////////////////////////////////////////////// INVENTORY SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character inventory.
	UPROPERTY(EditAnywhere, Category = "Character Inventory", meta = (AllowPrivateAccess))
	int batteryQuantity;

	UPROPERTY(EditAnywhere, Category = "Character Inventory", meta = (AllowPrivateAccess))
	int thowableQuantity;

	ETakeableType takeableType;

	////////////////////////////////////////////// LANTERN SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character lantern mechanic.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	class USpotLightComponent* lantern;

	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	class UCameraComponent* characterCamera;

	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float lanternIntensity = 800.0f;

	// Baterry flashlight properties.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float maxBatteryAmount = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float batteryWearAmount = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float currentBatteryAmount = 0.0f;

	// Methods that manage the lantern state.
	void LanternON();
	void LanternOFF();
	void SetLanternIntensity(float intensity);

	// Method that manage lantern's battery
	void UseLanternBattery();

	bool isLanternOn;

	FTimerHandle timeHandleFlashLight;

};
