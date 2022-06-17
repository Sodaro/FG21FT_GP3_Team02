#pragma once
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "SGPlayerCharacterLanternComponent.generated.h"

class UAudioComponent;
class USoundBase;
class USGProgressBarWidget;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoolDelegate, bool, Value);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatFloatDelegate, float, Current, float, Max);

UCLASS()
class USGPlayerCharacterLanternComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	USGPlayerCharacterLanternComponent();

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupLanternValues();
	void SwitchingLights(float DeltaTime);

	// Set Lantern Values
	void SetLightIntensity(float Intensity) { LightIntensity = Intensity; }

	// Lantern Battery Functions
	void DecreaseBattery(float DeltaTime);
	float GetBatteryTime() { return BatteryTimeKeeper; }
	void SetBatteryTime(float NewTimer) { BatteryTimeKeeper = NewTimer; }
	void HandleBatteryLevels();

	bool bLowBattery = false;
	// Lantern Battery Timers
	float TimeBeforeBatteryDecrease = 0.f;
	float CurrentBatteryTimer = 0.f;
	float BatteryTimer = 0.f;
	float BatteryTimeKeeper = 0.f;

	// Light Switch Timer
	float CurrentTime = 0.f;

	// Light Flickering
	void LightFlickering();
	int LightFlickeringCase = 0;

	float LightIntensity = 10000.f;
	float LightIntensitySAVED = 0.f;

	void UpdateIndicator();
	bool bNoBatteryLeft = false;

	float UVIntensity = 0.f;

public:
	bool bLanternActive = false;
	// Input Actions
	void ToggleLantern();
	void UVLantern();
	void NormalLantern();

	// Lantern Battery 
	UPROPERTY(BlueprintReadOnly)
	int BatteryMin = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int BatteryMax = 100;

	UFUNCTION(BlueprintCallable)
	void ChargeLantern();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int CurrentBattery = BatteryMax;

	//-----------INDICATOR---------------

	UPROPERTY(EditDefaultsOnly, Category = "Indicator | Colors")
	FLinearColor HighChargeColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, Category = "Indicator | Colors")
	FLinearColor MediumChargeColor = FLinearColor::Yellow;

	UPROPERTY(EditDefaultsOnly, Category = "Indicator | Colors")
	FLinearColor LowChargeColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "1", Category = "Indicator | Colors"))
	float MediumChargeUpperThreshold = 0.49f;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "1", Category = "Indicator | Colors"))
	float LowChargeUpperThreshold = 0.25f;

	//--------------AUDIO----------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Flashlight")
	USoundBase* LanternEnableSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Flashlight")
	USoundBase* LanternDisableSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | UV")
	USoundBase* UVEnableSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | UV")
	USoundBase* UVDisableSound;

	//-----------ENDAUDIO----------------

	UPROPERTY(EditAnywhere, Category = "LanternValues")
	float TimeBeforeChangingLight = 0.2f;
	float TimeBeforeChangeKeeper = TimeBeforeChangingLight;

	// Normal Lantern Values
	UPROPERTY(EditAnywhere, Category = "NormalLightValues")
	float NormalBatteryDrainTime = 3.f;

	// UV Lantern Values
	UPROPERTY(EditAnywhere, Category = "UVLightValues")
	float UVBatteryDrainTime = 1.f;

	// Lower Intensity
	UPROPERTY(EditAnywhere, Category = "LowerIntensity")
	float LowerIntensity = 5000.f;

	// Light Colors
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	FColor NormalColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	FColor UVColor;

	UPROPERTY(BlueprintAssignable)
	FBoolDelegate UVEnabledChanged;

	UPROPERTY(BlueprintAssignable)
	FBoolDelegate LanternEnabledChanged;

	void ToggleLanternModes();

	UPROPERTY(BlueprintReadOnly)
	bool bUVIsActive = false;

	FFloatFloatDelegate BatteryLevelChanged;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* Lantern;
};