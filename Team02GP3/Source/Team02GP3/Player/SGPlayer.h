#pragma once
#include "GameFramework/Pawn.h"
#include "SGPlayerControllerComponent.h"
#include "SGPlayerLantern.h"
#include "SGPlayerCamera.h"
#include "Components/CapsuleComponent.h"
#include "Team02GP3/SGSaveGame.h"
#include "SGPlayer.generated.h"

UCLASS()
class ASGPlayer : public APawn
{
	GENERATED_BODY()

private:

	ASGPlayer();

	void SetupPlayerInputComponent(UInputComponent* PlayerInput);

	void HandleForwardInput(float AxisValue);
	void HandleRightInput(float AxisValue);

	void HandleLanternPressedInput();
	void HandleLanternReleasedInput();

	void HandleTurnOnOffLantern();

	UPROPERTY(EditDefaultsOnly)
	USGPlayerControllerComponent* PlayerController;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditDefaultsOnly)
	USGPlayerLantern* Lantern;

	UPROPERTY(EditAnywhere)
	ASGPlayerCamera* PlayerCamera;



public:

	//void SaveGame();
	//void LoadGame();

	void HandleCharging();
};