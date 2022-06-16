#pragma once
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "SGPlayerControllerComponent.h"

#include "SGPlayerCamera.generated.h"

UCLASS()
class ASGPlayerCamera : public AActor
{
	GENERATED_BODY()

private:

	ASGPlayerCamera();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void FollowPlayer(float DeltaTime);
	void FollowMouse(float DeltaTime);

	bool bCameraFollowMouse;

	APlayerController* Controller;

	UPROPERTY(EditAnywhere)
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

public:

	UPROPERTY(EditAnywhere)
	float LocationOffsetX = 270.f;
	
	UPROPERTY(EditAnywhere)
	float LocationOffsetZ = 1000.f;

	void ToggleCameraFollow();
};