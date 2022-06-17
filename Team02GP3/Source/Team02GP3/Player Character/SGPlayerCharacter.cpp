#include "SGPlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "SGPlayerCharacterLanternComponent.h"
#include "SGPlayerCharacterCameraComponent.h"
#include "SGPlayerInteractionComponent.h"
#include "../MoveableBox/MoveableBox.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Widgets/SGPlayerUI.h"
#include "SGLogbook.h"
#include "Kismet/KismetMathLibrary.h"
#include "Team02GP3/SGSaveGame.h"

ASGPlayerCharacter::ASGPlayerCharacter()
{
	PlayerLantern = CreateDefaultSubobject<USGPlayerCharacterLanternComponent>(TEXT("PlayerLantern"));
	InteractionComponent = CreateDefaultSubobject<USGPlayerInteractionComponent>(TEXT("InteractionComponent"));
	PrimaryActorTick.bCanEverTick = true;
}

void ASGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = false;
	Controller = GetWorld()->GetFirstPlayerController();

	Acceleration = GetCharacterMovement()->MaxAcceleration;
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	StaminaDrainTimerSAVED = StaminaDrainTimer;
	StaminaRechargeTimerSAVED = StaminaRechargeTimer;

	if (PlayerUIClass == nullptr)
	{
		return;
	}

	PlayerLantern->UVEnabledChanged.AddDynamic(this, &ASGPlayerCharacter::OnUVEnabledChanged);

	PlayerUI = NewObject<USGPlayerUI>(this, PlayerUIClass);
	PlayerUI->Initialize(PlayerLantern, InteractionComponent);
	//PlayerUI->LogbookNotificationImage->SetVisibility(ESlateVisibility::Hidden);
	//PlayerUI->FlashlightProgressBar->SetVisibility(ESlateVisibility::Hidden);
	PlayerUI->AddToViewport();
	USGSaveGame* SaveGameInstance = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
	if (SaveGameInstance)
	{
		SetActorTransform(SaveGameInstance->PlayerTransform);
		PlayerLantern->CurrentBattery = SaveGameInstance->CurrentBattery;
		InteractionComponent->Logbook->AddEntries(SaveGameInstance->LogbookKeys);
	}
}

void ASGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotatePlayer && bIsSprinting == false)
	{
		//RotateActor(DeltaTime);
		RotateLantern(DeltaTime);
	}

	if (CurrentStamina <= 0.f)
	{
		SprintInnactive();
	}

	if (bIsSprinting && GetCharacterMovement()->Velocity.Size() > 0.f && bDrainStamina)
	{
		PlayerCamera->ZoomInCamera();
		DecreaseStamina(DeltaTime);
	}
	else
	{
		PlayerCamera->ZoomOutCamera();
		ReChargeStamina(DeltaTime);
	}
}

void ASGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	// Player Movement
	PlayerInput->BindAxis(TEXT("Vertical"), this, &ASGPlayerCharacter::HandleForwardInput);
	PlayerInput->BindAxis(TEXT("Horizontal"), this, &ASGPlayerCharacter::HandleRightInput);

	PlayerInput->BindAction(TEXT("Sprint"), IE_Pressed, this, &ASGPlayerCharacter::HandleSprintingPressed);
	PlayerInput->BindAction(TEXT("Sprint"), IE_Released, this, &ASGPlayerCharacter::HandleSprintingReleased);
	// Lantern
	PlayerInput->BindAction("LanternSwitch", IE_Pressed, this, &ASGPlayerCharacter::HandleRightClick);
	PlayerInput->BindAction("TurnOnOffLantern", IE_Pressed, this, &ASGPlayerCharacter::HandleLeftClick);

	// Journal
	PlayerInput->BindAction("ToggleJournal", IE_Pressed, this, &ASGPlayerCharacter::HandleToggleJournal);
	// Interactions
	PlayerInput->BindAction("Interact", IE_Pressed, this, &ASGPlayerCharacter::HandleMoveableInteraction);
	// Save/Load
	InputComponent->BindAction("Save", IE_Pressed, this, &ASGPlayerCharacter::SaveGame);
	InputComponent->BindAction("Load", IE_Pressed, this, &ASGPlayerCharacter::LoadGame);
}

void ASGPlayerCharacter::HandleForwardInput(float Value)
{
	if (bToggleJournal) return;

	GetCharacterMovement()->AddInputVector(GetActorLocation().XAxisVector * Value, false);
}

void ASGPlayerCharacter::HandleRightInput(float Value)
{
	if (bToggleJournal) return;

	GetCharacterMovement()->AddInputVector(GetActorLocation().YAxisVector * Value, false);
}

void ASGPlayerCharacter::HandleSprintingPressed()
{
	if (CurrentStamina <= MinStamina || bIsInteractingWithBox) { return; }
	PlayerCamera->bCharacterIsSprinting = true;
	SprintActive();
}

void ASGPlayerCharacter::HandleSprintingReleased()
{
	PlayerCamera->bCharacterIsSprinting = false;
	SprintInnactive();
}

void ASGPlayerCharacter::HandleLeftClick()
{
	if (bToggleJournal) return;

	// Normal Light
	if (PlayerLantern->bUVIsActive)
	{
		PlayerLantern->NormalLantern();
	}
	//else
	//{
	//	PlayerLantern->UVLantern();
	//}
}

void ASGPlayerCharacter::HandleRightClick()
{
	if (bToggleJournal) return;

	// UV Light
	if (PlayerLantern->bUVIsActive == false)
	{
		PlayerLantern->UVLantern();
	}
	//else
	//{
	//	PlayerLantern->NormalLantern();
	//}
}

void ASGPlayerCharacter::HandleToggleJournal()
{
	bToggleJournal = !bToggleJournal;
	PlayerCamera->bJournalIsOpen = !PlayerCamera->bJournalIsOpen;

	InteractionComponent->ToggleLogbookVisibility(bToggleJournal);
}

void ASGPlayerCharacter::RotateActor(float DeltaTime)
{
	if (bToggleJournal) return;

	FRotator TargetRotation = (MouseToWorld() - GetActorLocation()).Rotation();

	FRotator ActorRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);

	SetActorRotation(ActorRotation);
}

void ASGPlayerCharacter::SprintActive()
{
	bIsSprinting = true;
	bDrainStamina = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ASGPlayerCharacter::SprintInnactive()
{
	bIsSprinting = false;
	bDrainStamina = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->MaxAcceleration = Acceleration;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	PlayerCamera->ZoomOutCamera();
}

void ASGPlayerCharacter::DecreaseStamina(float DeltaTime)
{
	StaminaDrainTimer -= DeltaTime;

	if (StaminaDrainTimer <= 0.f && CurrentStamina > MinStamina)
	{
		CurrentStamina--;
		StaminaDrainTimer = StaminaDrainTimerSAVED;
	}
}

void ASGPlayerCharacter::ReChargeStamina(float DeltaTime)
{
	StaminaRechargeTimer -= DeltaTime;

	if (StaminaRechargeTimer <= 0.f && CurrentStamina < MaxStamina)
	{
		CurrentStamina++;
		StaminaRechargeTimer = StaminaRechargeTimerSAVED;
	}
}

void ASGPlayerCharacter::RotateLantern(float DeltaTime)
{
	FRotator TargetRotation = (MouseToWorld() - GetActorLocation()).Rotation();
	FQuat ForwardRotation = GetActorRotation().Quaternion();

	auto Location = (MouseToWorld() - GetActorLocation());
	Location.Normalize();

	float Dot = FVector::DotProduct(GetActorForwardVector(), Location);
	auto Radians = FMath::Acos(Dot);

	float Degrees = FMath::RadiansToDegrees(Radians);

	if (Degrees > Range)
	{
		auto InterpEPIC = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.f);
		SetActorRotation(InterpEPIC);
	}
	else
	{
		PlayerLantern->Lantern->SetWorldRotation(TargetRotation);
	}
}

void ASGPlayerCharacter::Teleport(int i)
{
	SetActorLocation(Positions[i]->GetActorLocation());
}

void ASGPlayerCharacter::ResetPlayer()
{
	bRotatePlayer = true;
	bIsInteractingWithBox = false;
}

FVector ASGPlayerCharacter::MouseToWorld()
{
	FVector WorldLocation;
	FVector WorldDirection;

	Controller->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector EndLocation = FMath::LinePlaneIntersection(
		WorldLocation,
		WorldLocation + (WorldDirection * 10000.f),
		GetActorLocation(),
		FVector::UpVector
	);

	return EndLocation;
}

TArray<FName>& ASGPlayerCharacter::GetLogbookKeys()
{
	return InteractionComponent->Logbook->GetUsedKeys();
}

void ASGPlayerCharacter::HandleMoveableInteraction()
{
	if (bIsInteractingWithBox)
	{
		DropBox();
	}
	else
	{
		PickUpBox();
	}
}

void ASGPlayerCharacter::PickUpBox()
{
	SetupLineTrace(90.f);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, LineStart, LineEnd, ECC_Visibility, CollisionParams))
	{
		if (Cast<AMoveableBox>(OutHit.Actor))
		{
			Cast<AMoveableBox>(OutHit.Actor)->HandleBoxInteraction(this);
			bRotatePlayer = false;
			bIsInteractingWithBox = true;
		}
	}
}

void ASGPlayerCharacter::DropBox()
{
	SetupLineTrace(100.f);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, LineStart, LineEnd, ECC_Visibility, CollisionParams))
	{
		if (Cast<AMoveableBox>(OutHit.Actor))
		{
			Cast<AMoveableBox>(OutHit.Actor)->HandleBoxInteraction(this);
			bRotatePlayer = true;
			bIsInteractingWithBox = false;
		}
	}
}

void ASGPlayerCharacter::SetupLineTrace(float TraceLength)
{
	LineLength = TraceLength;
	LineStart = GetActorLocation() - FVector(0.f, 0.f, 50.f);
	LineEnd = LineStart + (GetActorForwardVector() * LineLength);

	CollisionParams.AddIgnoredActor(this);
}

void ASGPlayerCharacter::OnUVEnabledChanged(bool Enabled)
{
	if (Enabled)
	{
		PlayerUI->ShowFlashlightIndicator();
	}
	else
	{
		PlayerUI->HideFlashlightIndicator();
	}
}
