#pragma once
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "SGPlayerControllerComponent.generated.h"

UCLASS(Meta=(BlueprintSpawnableComponent))
class USGPlayerControllerComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	USGPlayerControllerComponent();
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Owner = GetOwner();

	void MoveForward(float DeltaTime);
	void MoveRight(float DeltaTime);
	void RotateActor(float DeltaTime);
	

	APlayerController* Controller;

	FVector WorldLocation, WorldDirection;
	FVector ActorLocation;
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere)
	AActor* PlayerCamera;

public:
	FVector MouseToWorld();

	UPROPERTY(EditAnywhere)
	float Force = 200.f;

	float ForwardAxis = 0.f;
	float RightAxis = 0.f;

};