#pragma once
#include "GameFramework/Actor.h"
#include "SGInteractableActor.generated.h"

class USphereComponent;
class APawn;
class ASGPlayerCharacter;
class USGPlayerInteractionComponent;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerOverlapSignature, ASGPlayerCharacter*, Player, USGPlayerInteractionComponent*, InteractionComponent);

UCLASS()
class ASGInteractableActor : public AActor
{
	GENERATED_BODY()
protected:

	void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadOnly)
	bool bPlayerInZone;

	ASGInteractableActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* InteractionSphereComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> PlayerClass;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerOverlapEnter(const ASGPlayerCharacter* Player, const USGPlayerInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerOverlapExit(const ASGPlayerCharacter* Player, const USGPlayerInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameLoad(bool HasBeenInteractedWith);
	/**
	* Fires when the player presses/releases the interact key inside of the trigger.
	* @return true if key was pressed, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInteract(const ASGPlayerCharacter* Player, const bool IsKeyPressed);

	UPROPERTY(BlueprintAssignable)
	FPlayerOverlapSignature PlayerOverlapEnter;

	UPROPERTY(BlueprintAssignable)
	FPlayerOverlapSignature PlayerOverlapExit;

	UFUNCTION()
	void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	UFUNCTION()
	void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};