#include "MoveableBoxUnlock.h"
#include "MoveableBoxPlatform.h"

AMoveableBoxUnlock::AMoveableBoxUnlock()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMoveableBoxUnlock::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* X : NeededPlatforms)
	{
		AMoveableBoxPlatform* Platform = Cast<AMoveableBoxPlatform>(X);
		Platform->GetUnlock(this);
	}
}

void AMoveableBoxUnlock::CheckTotalLockedBoxes()
{
	PlatformsLocked++;
	if (PlatformsLocked == NeededPlatforms.Num())
	{
		// not final lmao
		Destroy();
	}
}