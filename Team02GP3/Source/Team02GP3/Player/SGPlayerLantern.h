#pragma once
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "SGPlayerLantern.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class USGPlayerLantern : public UActorComponent
{
	GENERATED_BODY()

private:

	USGPlayerLantern();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupLanternValues();
	void SwitchingLights(float DeltaTime);
	
	// Set Lantern Values
	// MEMO: Unsure if these will be used
	void SetLightIntensity(float Intensity) { LightIntensity = Intensity; }
	void SetInnerConeAngle(float Angle) { NormalInnerConeAngle = Angle; }
	void SetOuterConeAngle(float Angle) { NormalOuterConeAngle = Angle; }

	// Lantern Battery Functions
	void DecreaseBattery(float DeltaTime);
	float GetBatteryTime() { return BatteryTimeKeeper; }
	void SetBatteryTime(float NewTimer) { BatteryTimeKeeper = NewTimer; }
	void HandleBatteryLevels();

	// Lantern Battery 
	int BatteryMin = 0;
	int BatteryMax = 100;
	
	bool bLowBattery = false;
	// Lantern Battery Timers
	float TimeBeforeBatteryDecrease = 0.f;
	
	float BatteryTimer = 0.f;
	float BatteryTimeKeeper = 0.f;

	// Light Switch Timer
	float CurrentTime = 0.f;

	bool bLanternActive = false;
	// Light Flickering
	void LightFlickering();
	int LightFlickeringCase = 0;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* Lantern;

public:
	// Input Actions
	void ToggleLantern();
	void UVLantern();
	void NormalLantern();
	// Called from a handle function in SGPlayer.cpp
	void ChargeLantern();

	UPROPERTY(EditAnywhere, Category = "LanternValues")
	float TimeBeforeChangingLight = 0.2f; 
	float TimeBeforeChangeKeeper = TimeBeforeChangingLight;

	// Lantern Setup
	UPROPERTY(EditAnywhere, Category = "LanternValues")
	float LightIntensity = 10000.f;
	UPROPERTY(EditAnywhere, Category = "LanternValues")
	float AttenuationRadius = 1600.f;
	UPROPERTY(EditAnywhere, Category = "LanternValues")
	float SourceRadius = 1600.f;

	// Normal Lantern Values
	UPROPERTY(EditAnywhere, Category = "NormalLightValues")
	float NormalBatteryDrainTime = 3.f; 
	UPROPERTY(EditAnywhere, Category = "NormalLightValues")
	float NormalInnerConeAngle = 40.f;
	UPROPERTY(EditAnywhere, Category = "NormalLightValues")
	float NormalOuterConeAngle = 60.f;

	// UV Lantern Values
	UPROPERTY(EditAnywhere, Category = "UVLightValues")
	float UVBatteryDrainTime = 1.f; 
	UPROPERTY(EditAnywhere, Category = "UVLightValues")
	float UVInnerConeAngle = 10.f;
	UPROPERTY(EditAnywhere, Category = "UVLightValues")
	float UVOuterConeAngle = 20.f;

	// Lower Intensity
	UPROPERTY(EditAnywhere, Category = "LowerIntensity")
	float LowerIntensity = 5000.f;

	// Light Colors
	UPROPERTY(EditAnywhere, Category = "Colors")
	FColor NormalColor;
	UPROPERTY(EditAnywhere, Category = "Colors")
	FColor UVColor;

	int CurrentBattery = BatteryMax;
	float CurrentBatteryTimer = 0.f;
};
