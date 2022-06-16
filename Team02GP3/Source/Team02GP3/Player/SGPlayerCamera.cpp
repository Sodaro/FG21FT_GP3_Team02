#include "SGPlayerCamera.h"
#include "SGPlayerLantern.h"

ASGPlayerCamera::ASGPlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void ASGPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	FRotator CameraRotationAngle = FRotator(-65.f, 0.f, 0.f);
	PlayerCamera->SetWorldRotation(CameraRotationAngle);

	Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = true;
	Controller->SetViewTarget(this);
}

void ASGPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowPlayer(DeltaTime);

	//if(bCameraFollowMouse)
	//{
	//	FollowMouse(DeltaTime);
	//}
	//else 
	//{
	//}
}

void ASGPlayerCamera::FollowPlayer(float DeltaTime)
{
	FVector CameraLocation = PlayerCamera->GetRelativeLocation();
	FVector TargetLocation = (PlayerActor->GetActorLocation() + FVector(0.f,0.f,LocationOffsetZ)) - FVector(LocationOffsetX,0.f,0.f);

	FVector NewLocation = FMath::VInterpTo(CameraLocation, TargetLocation, DeltaTime, 1.f);
	// Camera Actor
	this->SetActorLocation(NewLocation);
}

void ASGPlayerCamera::FollowMouse(float DeltaTime)
{
	auto PlayerController = PlayerActor->FindComponentByClass<USGPlayerControllerComponent>();
	FVector MouseLocation = PlayerController->MouseToWorld();
	FVector ActorLocation = PlayerActor->GetActorLocation();

	float minX = PlayerActor->GetActorLocation().X - 300.f;
	float maxX = PlayerActor->GetActorLocation().X + 100.f;
	float MouseX = MouseLocation.X;

	float ClampedXValue = FMath::Clamp(MouseX, minX, maxX);

	float minY = PlayerActor->GetActorLocation().Y - 100.f;
	float maxY = PlayerActor->GetActorLocation().Y + 100.f;
	float MouseY = MouseLocation.Y;

	float ClampedYValue = FMath::Clamp(MouseY, minY, maxY);

	FVector CameraLocation = PlayerCamera->GetRelativeLocation();

	FVector ClampedLocation = FVector(ClampedXValue, ClampedYValue, LocationOffsetZ);

	FVector TargetLocation = ClampedLocation - FVector(LocationOffsetX, 0.f, 0.f);
	
	FVector NewCameraLocation = FMath::VInterpTo(CameraLocation, TargetLocation, DeltaTime, 1.f);
	// Camera Actor
	this->SetActorLocation(NewCameraLocation);
}

void ASGPlayerCamera::ToggleCameraFollow()
{
	bCameraFollowMouse = !bCameraFollowMouse;
}