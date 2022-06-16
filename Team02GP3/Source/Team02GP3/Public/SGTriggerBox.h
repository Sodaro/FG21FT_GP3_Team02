// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SGTriggerBox.generated.h"


UCLASS()
class TEAM02GP3_API ASGTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

public:
	ASGTriggerBox();

	UFUNCTION()
	void Event(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	AActor* Fountain;
};