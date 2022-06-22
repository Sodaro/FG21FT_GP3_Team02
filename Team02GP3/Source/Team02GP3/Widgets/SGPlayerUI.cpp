// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerUI.h"
#include "SGLogbook.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "SGPlayerInteractionComponent.h"
#include "../Player Character/SGPlayerCharacterLanternComponent.h"

void USGPlayerUI::Initialize(USGPlayerCharacterLanternComponent* LanternComp, USGPlayerInteractionComponent* InteractionComp)
{
	InteractionComp->Logbook->LogbookUpdated.AddDynamic(this, &USGPlayerUI::ShowLogbookNotification);
	LanternComp->BatteryLevelChanged.AddDynamic(this, &USGPlayerUI::UpdateBatteryIndicator);
}

void USGPlayerUI::ShowLogbookNotification(USGLogBook* Logbook)
{
	LogbookVB->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(LogNotificationAnim);
}

void USGPlayerUI::UpdateBatteryIndicator(float Current, float Max)
{
	FlashlightProgressBar->SetPercent(Current / Max);
}

void USGPlayerUI::ShowFlashlightIndicator()
{
	FlashlightRoot->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USGPlayerUI::HideFlashlightIndicator()
{
	FlashlightRoot->SetVisibility(ESlateVisibility::Hidden);
}
