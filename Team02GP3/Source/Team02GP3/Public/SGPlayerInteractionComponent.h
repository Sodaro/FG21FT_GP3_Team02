// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGPlayerInteractionComponent.generated.h"

class UTextRenderComponent;
class USGPlayerBarkWidget;
class USGLogBook;
class USGButtonWidget;
class UAudioComponent;
class USoundBase;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLogbookOpenDelegate, bool, Enabled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM02GP3_API USGPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USGPlayerInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float DisplayTimer = 0.f;
	bool DisplayTimerEnabled = false;

	void DisplayErrorAndQuit(FString Text);

public:	

	bool bIsLogbookDisplayed = false;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/**
	* Toggles the journal widget visibility on/off.
	*/

	UFUNCTION(BlueprintCallable)
	void ToggleLogbookVisibility();

	UFUNCTION()
	void ShowLogbook();
	
	UFUNCTION()
	void HideLogbook();

	UFUNCTION(BlueprintCallable)
	void ShowBarkText(const FString &Text, float Duration);

	UFUNCTION(BlueprintCallable)
	void DisplayPromptText(const FString &Text, AActor *Target, FVector LocationOffset);

	UFUNCTION(BlueprintCallable)
	void HidePromptText();

	UPROPERTY(BlueprintReadOnly)
	USGLogBook* Logbook;
	
	FLogbookOpenDelegate LogbookOpenChanged;
	//-----------Subclasses--------------

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USGPlayerBarkWidget> PlayerBarkWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USGLogBook> LogbookClass;

	//--------------Widgets----------------

	UPROPERTY()
	USGPlayerBarkWidget* PlayerBarkWidget;

	//TODO: Change classname of widget to a more generalized one
	UPROPERTY()
	USGPlayerBarkWidget* PromptWidget;

	//--------------AUDIO----------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Logbook")
	USoundBase* LogbookOpenSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Logbook")
	USoundBase* LogbookCloseSound;


};
