// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGProgressBarWidget.generated.h"

class UProgressBar;

UCLASS()
class TEAM02GP3_API USGProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBarWidget;
};
