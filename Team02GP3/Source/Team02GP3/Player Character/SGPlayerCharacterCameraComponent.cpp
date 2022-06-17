#include "SGPlayerCharacterCameraComponent.h"
#include "SGPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ASGPlayerCharacterCameraComponent::ASGPlayerCharacterCameraComponent()
{
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void ASGPlayerCharacterCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = true;
	Controller->SetViewTarget(this); 

	LocationOffset = GetActorLocation() - OtherActor->GetActorLocation();

	ZoomOutVector = LocationOffset;
	ZoomInVector = LocationOffset - ZoomInOffset;

	CameraRecenterSpeedSaved = CameraRecenterSpeed;

	Bounce = GetActorLocation().Z - OtherActor->GetActorLocation().Z;
	MinBounce = Bounce - 20.f;
	MaxBounce = Bounce + 20.f;

	ClampedBounce = FMath::Clamp(Bounce, MinBounce, MaxBounce);
}

void ASGPlayerCharacterCameraComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraBob(DeltaTime);

	if (bJournalIsOpen)
	{
		SetActorLocation(GetActorLocation());
	}
	else
	{
		FollowPlayer(DeltaTime);

		if (bCharacterIsSprinting == false)
		{
			FollowMouse(DeltaTime);
		}
	}
}

void ASGPlayerCharacterCameraComponent::FollowPlayer(float DeltaTime)
{
	FVector OffsetedActorLocation = OtherActor->GetActorLocation() + LocationOffset;
	//OffsetedActorLocation.Z = ClampedBounce;
	FVector CameraLocation = GetActorLocation();

	FVector TargetLocation = FMath::VInterpTo(CameraLocation, OffsetedActorLocation, DeltaTime, CameraRecenterSpeed);

	SetActorLocation(TargetLocation);
}

void ASGPlayerCharacterCameraComponent::FollowMouse(float DeltaTime)
{ 	
	FVector PlayerLocation = OtherActor->GetActorLocation();

	//FVector Offset = OtherActor->GetActorLocation() + LocationOffset;
	//
	//FVector MouseLocation = MouseToWorld();
	//MouseLocation.Z = PlayerLocation.Z;
	//
	//FVector Direction = (MouseLocation - OtherActor->GetActorLocation());
	//
	//if (Direction.Normalize())
	//{
	//	float Length = (MouseLocation - OtherActor->GetActorLocation()).Size();
	//	float MaxLength = 200.f;
	//	float MinLength = -200.f;
	//
	//	if (Length > MaxLength)
	//	{
	//		Length = MaxLength;
	//	}
	//	if (Length < MinLength)
	//	{
	//		Length = MinLength;
	//	}
	//
	//	FVector Target = (OtherActor->GetActorLocation() + (Direction * Length))  + FVector(0.f, 0.f, Offset.Z);
	//
	//	FVector NewTargetLocation = FMath::VInterpTo(GetActorLocation(), Target, DeltaTime, 5.f);
	//
	//	SetActorLocation(NewTargetLocation);
	//}

	FVector Offset = PlayerLocation + LocationOffset;
	
	FVector Min = FVector(PlayerLocation.X - CameraOffset, PlayerLocation.Y - CameraOffset, Offset.Z);
	FVector Max = FVector(PlayerLocation.X + CameraOffset, PlayerLocation.Y + CameraOffset, Offset.Z);

	//FVector Min = FVector(PlayerLocation.X - CameraOffset, PlayerLocation.Y - CameraOffset, MinBounce);
	//FVector Max = FVector(PlayerLocation.X + CameraOffset, PlayerLocation.Y + CameraOffset, MaxBounce);

	FVector ClampedTargetLocation = ClampVector(MouseToWorld(), Min, Max);
	
	FVector NewTargetLocation = FMath::VInterpTo(GetActorLocation(), ClampedTargetLocation, DeltaTime, MouseFollowSpeed);
	
	SetActorLocation(NewTargetLocation);
}

FVector ASGPlayerCharacterCameraComponent::MouseToWorld()
{
	FVector WorldLocation;
	FVector WorldDirection;

	Controller->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector EndLocation = FMath::LinePlaneIntersection(
		WorldLocation,
		WorldLocation + (WorldDirection * 10000.f),
		OtherActor->GetActorLocation(),
		FVector::UpVector
	);

	return EndLocation;
}

void ASGPlayerCharacterCameraComponent::CameraBob(float DeltaTime)
{
	if (bCameraBobActive) 
	{ 
		Timer -= DeltaTime;

		if(Timer >= 0.25f)
		{
			ClampedBounce += 60 * DeltaTime;
		}
		else
		{
			ClampedBounce -= 60 * DeltaTime;
		}

		if(Timer <= 0.f)
		{
			Timer = 0.5f;
		}
	}
}

void ASGPlayerCharacterCameraComponent::ZoomInCamera()
{	
	LocationOffset = ZoomInVector;
	CameraRecenterSpeed = 10.f;
}

void ASGPlayerCharacterCameraComponent::ZoomOutCamera()
{
	LocationOffset = ZoomOutVector;
	CameraRecenterSpeed = CameraRecenterSpeedSaved;
}