// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGPlayerBarkWidget.generated.h"

class UTextBlock;
class AActor;
UCLASS()
class TEAM02GP3_API USGPlayerBarkWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BarkTextBlock;

	UPROPERTY(BlueprintReadOnly)
	AActor* TargetActor;

	UPROPERTY(BlueprintReadOnly)
	FVector LocationOffset;
};
