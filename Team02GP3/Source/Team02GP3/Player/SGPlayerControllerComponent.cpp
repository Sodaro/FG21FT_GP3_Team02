#include "SGPlayerControllerComponent.h"
#include "SGPlayer.h"

USGPlayerControllerComponent::USGPlayerControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USGPlayerControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
}


void USGPlayerControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveForward(DeltaTime);
	MoveRight(DeltaTime);

	MouseToWorld();
	RotateActor(DeltaTime);

	FVector GravityVelocity = -FVector::UpVector * Force;
	Owner->AddActorWorldOffset(GravityVelocity * DeltaTime, true);
}

void USGPlayerControllerComponent::MoveForward(float DeltaTime)
{
	FVector Velocity = FVector::ForwardVector * Force * ForwardAxis;
	Owner->AddActorWorldOffset(Velocity * DeltaTime, true);
}

void USGPlayerControllerComponent::MoveRight(float DeltaTime)
{
	FVector Velocity = FVector::RightVector * Force * RightAxis;
	Owner->AddActorWorldOffset(Velocity * DeltaTime, true);
}

void USGPlayerControllerComponent::RotateActor(float DeltaTime)
{
	ActorLocation = Owner->GetActorLocation();
	TargetRotation = (MouseToWorld() - ActorLocation).Rotation();

	FRotator ActorRotation = FMath::RInterpTo(Owner->GetActorRotation(), TargetRotation, DeltaTime, 10.f);

	Owner->SetActorRotation(ActorRotation);
}

FVector USGPlayerControllerComponent::MouseToWorld()
{
	Controller->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector EndLocation = FMath::LinePlaneIntersection(
		WorldLocation,
		WorldLocation + (WorldDirection * 10000.f),
		ActorLocation,
		FVector::UpVector
	);

	return EndLocation;
}