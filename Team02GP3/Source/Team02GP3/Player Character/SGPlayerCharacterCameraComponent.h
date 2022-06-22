#pragma once
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "SGPlayerCharacterCameraComponent.generated.h"

UCLASS()
class ASGPlayerCharacterCameraComponent : public APawn
{
	GENERATED_BODY()

private:

	ASGPlayerCharacterCameraComponent();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void FollowPlayer(float DeltaTime);
	bool bCameraFollowMouse;

	void FollowMouse(float DeltaTime);

	FVector LocationOffset;

	float CameraRecenterSpeedSaved = 0.f;

	FVector MouseToWorld();

	APlayerController* Controller;

	UPROPERTY(EditAnywhere)
	AActor* OtherActor;

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	FVector ZoomOutVector = FVector::ZeroVector;
	FVector ZoomInVector = FVector::ZeroVector;

public:

	void ZoomInCamera();
	void ZoomOutCamera();

	UPROPERTY(EditAnywhere)
	float CameraOffset = 200.f;

	UPROPERTY(EditAnywhere)
	FVector ZoomInOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float MouseFollowSpeed = 5.f;

	UPROPERTY(EditAnywhere)
	float CameraRecenterSpeed = 1.f;

	bool bJournalIsOpen = false;

	bool bCharacterIsSprinting = false;
};