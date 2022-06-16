#pragma once
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MoveableBox.generated.h"

UCLASS()
class AMoveableBox : public AActor 
{
	GENERATED_BODY()
	AMoveableBox();

private:

	void Tick(float DeltaTime);
	void MoveBox(AActor* OtherActor);

	FVector poopie = FVector(0.f, 0.f, 40.f);

public:

	void DropBox();

	bool bIsBeingMoved = false;

	void HandleBoxInteraction(AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Spherex;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Spherey;

	AActor* PlayerActor;
};