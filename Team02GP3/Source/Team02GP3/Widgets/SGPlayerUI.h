// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGPlayerUI.generated.h"

class USGPlayerCharacterLanternComponent;
class USGPlayerInteractionComponent;
class UProgressBar;
class UImage;
class USGLogBook;
class UOverlay;
class UVerticalBox;

UCLASS()
class TEAM02GP3_API USGPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:

	void Initialize(USGPlayerCharacterLanternComponent* LanternComp, USGPlayerInteractionComponent* InteractionComp);

	UFUNCTION()
	void ShowLogbookNotification(USGLogBook* Logbook);

	UFUNCTION()
	void UpdateBatteryIndicator(float Current, float Max);

	void ShowFlashlightIndicator();
	void HideFlashlightIndicator();

	UPROPERTY(meta = (BindWidget))
	UProgressBar* FlashlightProgressBar;

	UPROPERTY(meta = (BindWIdget))
	UVerticalBox* LogbookVB;

	UPROPERTY(meta = (BindWidget))
	UImage* LogbookNotificationImage;

	UPROPERTY(meta = (BindWidget))
	UOverlay* FlashlightRoot;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* LogNotificationAnim;
};
