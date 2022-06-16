#pragma once
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGPlayerCharacterCameraComponent.h"
#include "SGPlayerCharacter.generated.h"

class SGPlayerInteractionComponent;
class USGPlayerCharacterLanternComponent;
class USGPlayerInteractionComponent;
class USGPlayerUI;
class USGLogBook;
UCLASS()
class ASGPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	ASGPlayerCharacter();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInput);
	
	void HandleForwardInput(float Value);
	void HandleRightInput(float Value);

	void HandleSprintingPressed();
	void HandleSprintingReleased();
	
	bool bIsSprinting = false;
	float Acceleration = 0.f;
	float WalkSpeed = 0.f;

	// for controller support (?)
	void HandleControllerPitchRotation(float Value);
	void HandleControllerYawRotation(float Value);

	void HandleLanternToggle();
	void HandleToggleLanternModes();
	
	void HandleToggleJournal();

	void HandleMoveableInteraction();
	void PickUpBox();
	void DropBox();
	void SetupLineTrace(float TraceLength);

	FHitResult OutHit;
	FVector LineStart = FVector::ZeroVector;
	FVector LineEnd = FVector::ZeroVector;

	float LineLength = 0.f;

	FCollisionQueryParams CollisionParams;

	void RotateActor(float DeltaTime);

	bool bRotatePlayer = true;
	bool bIsInteractingWithBox = false;
	bool bToggleJournal = false;

	
	float CurrentStamina = MaxStamina;
	float MinStamina = 0.f;

	float StaminaDrainTimerSAVED = 0.f;
	float StaminaRechargeTimerSAVED = 0.f;

	bool bDrainStamina = false;

	void SprintActive();
	void SprintInnactive();

	void DecreaseStamina(float DeltaTime);
	void ReChargeStamina(float DeltaTime);

	//---------------------TEST------------------//
	bool bLanternActive = false;
	bool bUVActive = false;

	void ToggleTEST();
	bool bTEST = false;

public:

	APlayerController* Controller;

	UPROPERTY(EditAnywhere)
	ASGPlayerCharacterCameraComponent* PlayerCamera;

	void ResetPlayer();
	/*
	* Todo: move lantern sounds to lantern
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Logbook")
	TSubclassOf<USGPlayerUI> PlayerUIClass;

	UPROPERTY()
	USGPlayerUI* PlayerUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USGPlayerCharacterLanternComponent* PlayerLantern;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USGPlayerInteractionComponent* InteractionComponent;

	FVector MouseToWorld();

	UPROPERTY(EditAnywhere, Category="RotationSpeed")
	float RotationSpeed = 3.f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float MaxAcceleration = 400.f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float MaxWalkSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float StaminaDrainTimer = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float StaminaRechargeTimer = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float MaxStamina = 100.f;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
};