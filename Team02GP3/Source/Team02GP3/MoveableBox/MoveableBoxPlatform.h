#pragma once
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MoveableBoxUnlock.h"
#include "MoveableBoxPlatform.generated.h"

UCLASS()
class AMoveableBoxPlatform : public AActor 
{
	GENERATED_BODY()
	AMoveableBoxPlatform();

private:
	void LockBox(AActor* Box);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	AMoveableBoxUnlock* Unlock = nullptr;

	bool bBoxIsPlaced = false;

public:

	bool bOnlyCallOnce = true;
	void GetUnlock(AActor* BoxUnlock);

	bool bBoxIsLockedIn = false;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
	AActor* Player;
};