#pragma once

#include "CoreMinimal.h"
#include "SGInteractableActor.h"
#include "Player/SGPlayerLantern.h"
#include "SGCheckpoint.generated.h"

UCLASS()
class TEAM02GP3_API ASGCheckpoint : public ASGInteractableActor
{
	GENERATED_BODY()

public:
	ASGCheckpoint();

	bool hasEntered = false;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};