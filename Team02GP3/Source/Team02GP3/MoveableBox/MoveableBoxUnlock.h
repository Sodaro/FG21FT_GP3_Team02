#pragma once
#include "GameFramework/Actor.h"
#include "MoveableBoxUnlock.generated.h"

UCLASS()
class AMoveableBoxUnlock : public AActor 
{
	GENERATED_BODY()
	AMoveableBoxUnlock();

private:

	void BeginPlay() override;

public:

	void CheckTotalLockedBoxes();

	int PlatformsLocked = 0;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> NeededPlatforms;
};