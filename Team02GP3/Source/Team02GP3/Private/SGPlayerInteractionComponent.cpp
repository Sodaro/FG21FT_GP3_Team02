// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerInteractionComponent.h"
#include "../Widgets/SGPlayerBarkWidget.h"
#include "SGLogBook.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Misc/MessageDialog.h"

USGPlayerInteractionComponent::USGPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("InteractionAudioComponent"));
}

void USGPlayerInteractionComponent::DisplayErrorAndQuit(FString Text)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Text);
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Text));
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetOuter(), 0);
	UKismetSystemLibrary::QuitGame(Controller, Controller, EQuitPreference::Type::Quit, true);
}

void USGPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerBarkWidgetClass == nullptr)
	{
		DisplayErrorAndQuit("PlayerBarkWidgetClass in InteractionComponent must be assigned.");
		return;
	}
	if (LogbookClass == nullptr)
	{
		DisplayErrorAndQuit("LogbookClass in PlayerInteractionComponent must be assigned");
		return;
	}

	Logbook = NewObject<USGLogBook>(this, LogbookClass);
	Logbook->SetVisibility(ESlateVisibility::Hidden);
	Logbook->AddToViewport(1);

	Logbook->LogCloseButton->OnClicked.AddDynamic(this, &USGPlayerInteractionComponent::HideLogbook);

	PlayerBarkWidget = NewObject<USGPlayerBarkWidget>(this, PlayerBarkWidgetClass);
	PlayerBarkWidget->TargetActor = Cast<AActor>(GetOuter());
	PlayerBarkWidget->LocationOffset = FVector{ 0,0,100 };

	PlayerBarkWidget->AddToViewport();
	PlayerBarkWidget->SetVisibility(ESlateVisibility::Hidden);

	PromptWidget = NewObject<USGPlayerBarkWidget>(this, PlayerBarkWidgetClass);
	PromptWidget->AddToViewport();
	PromptWidget->SetVisibility(ESlateVisibility::Hidden);
}

void USGPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector2D ViewportPosition;
	if (PromptWidget != nullptr && PromptWidget->TargetActor != nullptr)
	{
		Controller->ProjectWorldLocationToScreen(PromptWidget->TargetActor->GetActorLocation() + PromptWidget->LocationOffset, ViewportPosition, false);
		PromptWidget->SetPositionInViewport(ViewportPosition, true);
	}

	if (PlayerBarkWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInteractionComponent tried to dereference BarkWidget which is null"));
		return;
	}

	if (PlayerBarkWidget->TargetActor != nullptr)
	{
		Controller->ProjectWorldLocationToScreen(PlayerBarkWidget->TargetActor->GetActorLocation() + PlayerBarkWidget->LocationOffset, ViewportPosition, false);
		PlayerBarkWidget->SetPositionInViewport(ViewportPosition, true);
	}

	if (DisplayTimer <= 0 && DisplayTimerEnabled == true)
	{
		DisplayTimerEnabled = false;
		PlayerBarkWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	DisplayTimer -= DeltaTime;
}

void USGPlayerInteractionComponent::ToggleLogbookVisibility()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bIsLogbookDisplayed = !bIsLogbookDisplayed;
	if (bIsLogbookDisplayed)
	{
		ShowLogbook();
	}
	else
	{
		HideLogbook();
	}
}

void USGPlayerInteractionComponent::ShowLogbook()
{
	bIsLogbookDisplayed = true;
	AudioComponent->Sound = LogbookOpenSound;
	if (AudioComponent->Sound != nullptr)
	{
		AudioComponent->Play();
	}
	Logbook->SetVisibility(ESlateVisibility::Visible);
	LogbookOpenChanged.Broadcast(true);
}

void USGPlayerInteractionComponent::HideLogbook()
{
	bIsLogbookDisplayed = false;
	AudioComponent->Sound = LogbookCloseSound;
	if (AudioComponent->Sound != nullptr)
	{
		AudioComponent->Play();
	}
	Logbook->SetVisibility(ESlateVisibility::Collapsed);
	LogbookOpenChanged.Broadcast(false);
}

void USGPlayerInteractionComponent::ShowBarkText(const FString& Text, float Duration)
{
	if (Duration <= 0)
		return;

	if (PlayerBarkWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInteractionComponent tried to dereference BarkWidget which is null"));
		return;
	}
	DisplayTimerEnabled = true;

	PlayerBarkWidget->BarkTextBlock->SetText(FText::FromString(Text));
	PlayerBarkWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	DisplayTimer = Duration;
}

void USGPlayerInteractionComponent::DisplayPromptText(const FString& Text, AActor* Target, FVector LocationOffset)
{
	if (PromptWidget == nullptr)
	{
		return;
	}
	if (Target == nullptr)
	{
		PromptWidget->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	PromptWidget->LocationOffset = LocationOffset;
	PromptWidget->TargetActor = Target;
	PromptWidget->BarkTextBlock->SetText(FText::FromString(Text));
	PromptWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USGPlayerInteractionComponent::HidePromptText()
{
	if (PromptWidget == nullptr)
	{
		return;
	}
	PromptWidget->SetVisibility(ESlateVisibility::Collapsed);
}

