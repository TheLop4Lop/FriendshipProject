// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacterController.h"
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

float const MaxAnxiety = 100; // Max anxiety value const.
float const ZeroVal = 0; // Zero value const.

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

	// Methods that handle in public increace and decreace anxiety on TriggerLuminare Class.
	void IncreaseAnxietyOnCharacter();
	// Change boolean condition values to access relax mechanic.
	void SetConditionsToRelax(bool relax);
	// Returns the current anxiety period.
	float GetAnxietyPeriod();
	// Returns the current anxiety level.
	float GetAnxietyLevel();
	// Returns wether or not the player is sprinting.
	bool isCharacterSptinting();

	// Calls mainWidget to add a dialog, depends on world interaction or mechanic.
	void SituationDialog(FString dialog);

	// Method that handles keys inventory, checks if player has the correct key.
	bool HasKeyToOpenDoor(FName door);

private:
	// Player's controller.
	class ABaseCharacterController* characterController;

	////////////////////////////////////////////// WIDGET SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character's Widget.

	// Widget subclass, contains reference to main interaction Widget.
	UPROPERTY(EditAnywhere, Category = "Character Widget", meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> mainWidgetClass;

	// Points to Main Interaction Widget.
	class UMainUIWidget* mainWidget;

	// Method that implements Widget Class.
	void SetWidgetInteractionClass(); 

	////////////////////////////////////////////// MOVEMENT SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character movement and control.

	// Walk speed of movement on character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float WalkSpeed = 600.0f;

	// Sprint speed of movement on character.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float SprintSpeed = 900.0f;

	// Controller Y Axis sensibility rate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float yAxisRate = 5.0f;

	// Controller X Axis sensibility rate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess))
    float xAxisRate = 5.0f;

	// Sound effect for character steps.
	UPROPERTY(EditAnywhere, Category = "Character Movement", meta = (AllowPrivateAccess))
	USoundBase* stepsSound;

	// Method that manage the spring mechanic.
	void Sprint();
	// Method that manage the walk mechanic.
	void Walk();
	
	// Funtion pointer, this pointer change its value  on character movement when Max Anxiety is reached.
	void (ABaseCharacter::*movementFunction1)(float) = nullptr;
	// Funtion pointer, this pointer change its value  on character movement when Max Anxiety is reached.
	void (ABaseCharacter::*movementFunction2)(float) = nullptr;

	// Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
	void HandleMovementInputAxis1(float value);
	// Methods that controll the Forward or Rigth direction, this movement depends on the funtion pointer.
	void HandleMovementInputAxis2(float value);

	// Movement Forward method.
	void MoveForward(float value);
	// Movement Right method.
	void MoveRigth(float value);

	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached.
	void (ABaseCharacter::*lookFunction1)(float) = nullptr;
	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached.
	void (ABaseCharacter::*lookFunction2)(float) = nullptr;

	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached. ON CONTROLLER
	void (ABaseCharacter::*lookFunction3)(float) = nullptr;
	// Funtion pointer, this pointer change its value  on character look and turn when Max Anxiety is reached. ON CONTROLLER
	void (ABaseCharacter::*lookFunction4)(float) = nullptr;

	// Method that controll the look and turn, this movement depens on the function pointer.
	void HandleLookInputAxis1(float value);
	// Method that controll the look and turn, this movement depens on the function pointer.
	void HandleLookInputAxis2(float value);

	// Look up Method.
	void LookUp(float value);
	// Turn Method.
	void TurnRight(float value);

	// Look up Method. ON CONTROLLER
	void LookUpController(float value);
	// Turn Method. ON CONTROLLER
	void TurnRightController(float value);

	// Methods used to define keyboard controller. (This can be unimplemented)
	void SetUsingKeyBoard();
	// Methods used to define gamepad controller. (This can be unimplemented)
	void SetUsingController(float value);

	// Sets Camera animation by movement.
	void SetCameraActionMovement();

	// Control Swap state.
	bool controlSwap = false;
	// Control step state.
	bool doOnceStep = true;

	// Test function for steps functionality.
	void stepiStp();

	// Timer for steps sound regulation.
	FTimerHandle timeStep;

	////////////////////////////////////////////// ANXIETY SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character anxiety mechanic.

	// Max value of stamina, this can change depending on the game. ()
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float maxStaminaByAnxiety = 30.0f;

	// Max value of anxiety period calls.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float maxAnxietyPeriod = 0.0625f;

	// Actual value of anxiety period call.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyPeriod;

	// Quantity of anxiety to increment.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyAmount;
	
	// Actual quantity of anxiety on player.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	float anxietyLevel;

	// Sound effect for character heart.
	UPROPERTY(EditAnywhere, Category = "Anxiety Mechanic", meta = (AllowPrivateAccess))
	USoundBase* heartSound;

	// Methods than manage the anxiety increasing value.
	void IncreaseAnxiety();
	// Sets initial conditions to manage the reduction on anxiety.
	void SetReduceAnxiety();
	// Methods than manage the anxiety reduction value.
	void ReduceAnxiety();

	// Control sprint state.
	bool isSprinting;
	// Control relax state.
	bool canRelax;
	// Control relax state repetition.
	bool doOnceRelax;
	// Control heart state repetition.
	bool doOnceHeart = true;

	//Timer to handle anxiety mechanic.
	FTimerHandle timeHandle;
	//Timers to handle heart sound anxiety mechanic.
	FTimerHandle timeHeart;

	// Sets initial condition to call heartbeat.
	void SetHeartSound();
	// Plays Heartbeat sound.
	void CheckAndPlayHeartSound();

	////////////////////////////////////////////// INTERACTION SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character interaction mechanic.

	// Max throw capacity range.
	UPROPERTY(EditAnywhere, Category = "Character Throw", meta = (AllowPrivateAccess))
	float throwRange = 200.0f;

	// Max pick capacity range;
	UPROPERTY(EditAnywhere, Category = "Character Pick", meta = (AllowPrivateAccess))
	float pickRange = 80.0f;

	// Duration of dialog on widget.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float dialogDuration = 3.0f;

	// Methods that manage the conditons to aim, this calls a Widget and determine conditions to damage actors.
	void Aim();
	// Stops aiming an removes the wigdet.
	void StopAim();
	// Generate linetrace collision to object (May be updated to spawn object).
	void ThrowProjectile();

	// Set GetActorToInteractInTheWorld function.
	void SetGetActorToInteractInTheWorldWidget();
	// Get the actor on player sight, this adds interaction on widget, depends of the type of object.
	void GetActorToInteractInTheWorld();
	// Method that return and interact with the actors in the world.
	AActor* ActorTargetByLineTrace(FHitResult& result, float& range);
	//Stores the the actor on players sight, this is use for throw mechanic.
	AActor* actorInSight;

	// Method that interct with BaseTakeable class, add value into players inventory variables, this depends on the Takeable enum.
	void TakeObject();
	//Stores the the actor on players sight, this is use for take mechanic.
	ABaseTakeable* pickableActor;
	//Stores the the actor on players sight, this is use for door mechanic.
	class ABaseDoor* currentDoor;
	
	// Hit structure of actor in sight. 
	FHitResult Hit;

	// Variable that stores Destroy tag, this is checked for interaction.
	FName TagDestroyableActor = FName("Destroy");
	// Variable that stores Takeable tag, this is checked for interaction.
	FName TagTakeableActor = FName("Takeable");

	// Control aiming state.
	bool isAiming;

	////////////////////////////////////////////// INVENTORY SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character inventory.

	// Quantity of batteries the player has taken from the world.
	UPROPERTY(EditAnywhere, Category = "Character Inventory", meta = (AllowPrivateAccess))
	int batteryQuantity;

	// Quantity of throables the player has taken from the world.
	UPROPERTY(EditAnywhere, Category = "Character Inventory", meta = (AllowPrivateAccess))
	int thowableQuantity;

	// Quantity of keys the player has taken from the world, each of them only open one door.
	UPROPERTY(EditAnywhere, Category = "Character Inventory", meta = (AllowPrivateAccess))
	int keyQuantity;

	// Actual keys the player has taken from the world, each of them only open one door.
	TArray<FName> keyTags;

	// Enum variable, keeps track of takeable type from tooked actor on sight.
	ETakeableType takeableType;

	////////////////////////////////////////////// LANTERN SECTION //////////////////////////////////////////////
	// This section contains properties and methods related to character lantern mechanic.

	// Latern class, used for exploration.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	class USpotLightComponent* lantern;

	// Camera class, interacts with lantern and movement animation from player's controller.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	class UCameraComponent* characterCamera;

	// Intensity of light from the lantern.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float lanternIntensity = 800.0f;

	// Baterry max capability.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float maxBatteryAmount = 100.0f;

	// Consumed quantity of baterry ratio.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float batteryWearAmount = 0.1f;

	// Actual battery amount on flashlight.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float currentBatteryAmount = 0.0f;

	// Time needed to change battery.
	UPROPERTY(EditAnywhere, Category = "Character Lartern", meta = (AllowPrivateAccess))
	float rechargeDelay = 2.5f;

	// Turn ON flashlight.
	void LanternON();
	// Turn OFF flashlight.
	void LanternOFF();
	// Set initial light intensity.
	void SetLanternIntensity(float intensity);

	// Method that manage lantern's battery
	void UseLanternBattery();
	// Method that manage recharge battery logic.
	void NewBatteryOnFlashlight();

	// Controls lantern state.
	bool isLanternOn;

	// Timer to handle the battery wear.
	FTimerHandle timeHandleFlashLight;
	// Timer to handle battery recharge.
	FTimerHandle timeFlashLightRecharge;

};
