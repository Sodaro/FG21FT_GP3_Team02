#include "SGPlayer.h"
#include "SGPlayerControllerComponent.h"


ASGPlayer::ASGPlayer()
{
	PlayerController = CreateDefaultSubobject<USGPlayerControllerComponent>(TEXT("MovementComponent"));
	Lantern = CreateDefaultSubobject<USGPlayerLantern>(TEXT("PlayerLantern"));
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleCollider;
}

void ASGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	//InputComponent->BindAction("Save", IE_Pressed, this, &ASGPlayer::SaveGame);
	//InputComponent->BindAction("Load", IE_Pressed, this, &ASGPlayer::LoadGame);
	// Player Movement
	PlayerInput->BindAxis("Vertical", this, &ASGPlayer::HandleForwardInput);
	PlayerInput->BindAxis("Horizontal", this, &ASGPlayer::HandleRightInput);
	// Normal and UV light switch
	PlayerInput->BindAction("LanternSwitch", IE_Pressed, this, &ASGPlayer::HandleLanternPressedInput);
	PlayerInput->BindAction("LanternSwitch", IE_Released, this, &ASGPlayer::HandleLanternReleasedInput);
	// Turn on and off light
	PlayerInput->BindAction("TurnOnOffLantern", IE_Pressed, this, &ASGPlayer::HandleTurnOnOffLantern);
}

void ASGPlayer::HandleForwardInput(float AxisValue)
{
	PlayerController->ForwardAxis = AxisValue;
}

void ASGPlayer::HandleRightInput(float AxisValue)
{
	PlayerController->RightAxis = AxisValue;
}

void ASGPlayer::HandleLanternPressedInput()
{
	Lantern->UVLantern();
}

void ASGPlayer::HandleLanternReleasedInput()
{
	Lantern->NormalLantern();
}

void ASGPlayer::HandleTurnOnOffLantern()
{
	PlayerCamera->ToggleCameraFollow();
	Lantern->ToggleLantern();
}

void ASGPlayer::HandleCharging() 
{
	// Called here instead of SGPlayerLantern because I couldn't get it to work
	// Called from SGChargingStation.cpp
	Lantern->ChargeLantern();
}