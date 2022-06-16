// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TEAM02GP3_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
		AEnemyAIController();

	UFUNCTION()
		void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		UAIPerceptionComponent* PerceptionComp = nullptr;

	UPROPERTY()
		UBlackboardComponent* BlackboardComp = nullptr;

	UPROPERTY()
		UCharacterMovementComponent* CharMoveComp = nullptr;
};
