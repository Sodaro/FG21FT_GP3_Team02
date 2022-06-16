#pragma once
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "SGChargingStation.generated.h"

UCLASS()
class ASGChargingStation : public AActor 
{
	GENERATED_BODY()

private:

	ASGChargingStation();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent* Light;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;
};