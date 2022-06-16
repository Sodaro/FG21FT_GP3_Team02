#include "SGPlayerLantern.h"
#include "DrawDebugHelpers.h"

USGPlayerLantern::USGPlayerLantern()
{
	PrimaryComponentTick.bCanEverTick = true;

	Lantern = CreateDefaultSubobject<USpotLightComponent>(TEXT("Lantern"));

	SetupLanternValues();
}

void USGPlayerLantern::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DecreaseBattery(DeltaTime);

	if (bLanternActive) 
	{
		SwitchingLights(DeltaTime);
	}
}

void USGPlayerLantern::ToggleLantern()
{
	bLanternActive = !bLanternActive;

	if (bLanternActive)
	{
		SetupLanternValues();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Lantern is ON");
	}
	else 
	{
		Lantern->SetIntensity(0.f);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Lantern is OFF");
	}
}

void USGPlayerLantern::UVLantern()
{
	SetBatteryTime(UVBatteryDrainTime);

	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(UVColor);
	//Lantern->SetInnerConeAngle(UVInnerConeAngle);
	//Lantern->SetOuterConeAngle(UVOuterConeAngle);
}

void USGPlayerLantern::NormalLantern()
{
	SetBatteryTime(NormalBatteryDrainTime);
	
	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(NormalColor);
	Lantern->SetInnerConeAngle(NormalInnerConeAngle);
	Lantern->SetOuterConeAngle(NormalOuterConeAngle);
}

void USGPlayerLantern::ChargeLantern()
{
	CurrentBattery = BatteryMax;

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "FULLY CHARGED");
}

void USGPlayerLantern::SetupLanternValues()
{
	SetBatteryTime(NormalBatteryDrainTime);
	
	Lantern->SetLightColor(NormalColor);
	Lantern->AttenuationRadius = AttenuationRadius;
	Lantern->SourceRadius = SourceRadius;
	Lantern->SetIntensity(LightIntensity);
}

void USGPlayerLantern::SwitchingLights(float DeltaTime)
{
	TimeBeforeChangingLight -= DeltaTime;
	CurrentTime = TimeBeforeChangingLight;

	if (CurrentTime <= 0.f)
	{
		Lantern->SetIntensity(LightIntensity);
	}
	else
	{
		Lantern->SetIntensity(0.f);
	}
}

void USGPlayerLantern::DecreaseBattery(float DeltaTime)
{
	if (bLanternActive)
	{
		BatteryTimer -= DeltaTime;
		CurrentBatteryTimer = BatteryTimer;

		if (CurrentBatteryTimer <= 0.f && CurrentBattery >= BatteryMin)
		{
			CurrentBattery--;

			HandleBatteryLevels();

			BatteryTimer = BatteryTimeKeeper;

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::FromInt(CurrentBattery));
		}
	}
}

void USGPlayerLantern::LightFlickering()
{
	if (bLowBattery == false || bLanternActive == false || CurrentBattery <= 0) { return; }

	float RandomSeconds = FMath::RandRange(0.f, 1.f);
	float WaitForSeconds = 0.2f;

	float RandomStrongIntensity = FMath::RandRange(LowerIntensity - 200.f, LowerIntensity);
	float RandomWeakIntensity = FMath::RandRange(LowerIntensity - 4000.f,LowerIntensity - 2000.f);

	switch (LightFlickeringCase)
	{
	case 0:
		// Stronger light
		SetLightIntensity(RandomStrongIntensity);

		WaitForSeconds = RandomSeconds;
		LightFlickeringCase++;
		break;
	case 1:
		// Weaker light
		SetLightIntensity(RandomWeakIntensity);

		WaitForSeconds = RandomSeconds;
		LightFlickeringCase = 0;
		break;
	}
	
	// FTimer
	FTimerHandle ChangeLanternTimer;

	GetWorld()->GetTimerManager().SetTimer
	(
		ChangeLanternTimer,
		this,
		&USGPlayerLantern::LightFlickering,
		WaitForSeconds,
		false
	);
}

void USGPlayerLantern::HandleBatteryLevels()
{

	switch (CurrentBattery)
	{
	case 100:
	case 99:
	case 50:
		// 100% - 50% HighCharger, Normal Intensity and Range
		SetupLanternValues();
		bLowBattery = false;
		break;
	case 49:
	case 20:
		// 49% - 20% MediumCharge, Decreased Intensity and Range
		SetLightIntensity(LowerIntensity);

		bLowBattery = false;
		break;
	case 19:
	case 1:
		// 19% - 1% LowCharge, Decreased Intensity and Range + Flickering 
		bLowBattery = true;
		LightFlickering();
		break;
	case 0:
		SetLightIntensity(0.f);
		break;
	default:
		break;
	}
}
