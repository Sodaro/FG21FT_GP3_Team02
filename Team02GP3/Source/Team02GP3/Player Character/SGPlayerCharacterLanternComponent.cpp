#include "SGPlayerCharacterLanternComponent.h"
#include "Components/AudioComponent.h"
#include "../Widgets/SGProgressBarWidget.h"


USGPlayerCharacterLanternComponent::USGPlayerCharacterLanternComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Lantern = CreateDefaultSubobject<USpotLightComponent>(TEXT("Lantern"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LanternAudioComponent"));
}

void USGPlayerCharacterLanternComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupLanternValues();

	LightIntensitySAVED = LightIntensity;
	
	//CurrentBattery = BatteryMax;

	Lantern->SetIntensity(0.f);
	bLanternActive = false;

	//if (LanternIndicatorClass == nullptr)
	//	return;

	//Create Indicator
	//LanternIndicatorWidget = NewObject<USGProgressBarWidget>(this, LanternIndicatorClass);
	//LanternIndicatorWidget->AddToViewport();

	//if (bLanternActive == false)
	//	LanternIndicatorWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void USGPlayerCharacterLanternComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DecreaseBattery(DeltaTime);

	if (bLanternActive)
	{
		SwitchingLights(DeltaTime);
	}
}

void USGPlayerCharacterLanternComponent::SetupLanternValues()
{
	SetBatteryTime(NormalBatteryDrainTime);

	LightIntensity = Lantern->Intensity;

	Lantern->SetLightColor(NormalColor);
}

void USGPlayerCharacterLanternComponent::SwitchingLights(float DeltaTime)
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

void USGPlayerCharacterLanternComponent::DecreaseBattery(float DeltaTime)
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

			BatteryLevelChanged.Broadcast(CurrentBattery, BatteryMax);
		}
	}
}

void USGPlayerCharacterLanternComponent::HandleBatteryLevels()
{
	switch (CurrentBattery)
	{
	case 100:
	case 99:
	case 50:
	case 49:
	case 20:
		// 100% - 20% HighCharger, Normal Intensity and Range
		LightIntensity = LightIntensitySAVED;
		bLowBattery = false;
		break;
	case 19:
	case 1:
		// 19% - 1% LowCharge, Decreased Intensity and Range + Flickering 
		bLowBattery = true;
		LightFlickering();
		break;
	case 0:
		// 0% No Light Intensity
		SetLightIntensity(0.f);
		break;
	default:
		break;
	}
}

void USGPlayerCharacterLanternComponent::LightFlickering()
{
	if (bLowBattery == false || bLanternActive == false || CurrentBattery <= 0) { return; }

	float RandomSeconds = FMath::RandRange(0.f, 1.f);
	float WaitForSeconds = 0.2f;

	float RandomStrongIntensity = FMath::RandRange(LowerIntensity - 200.f, LowerIntensity);
	float RandomWeakIntensity = FMath::RandRange(LowerIntensity - 4000.f, LowerIntensity - 2000.f);

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
		&USGPlayerCharacterLanternComponent::LightFlickering,
		WaitForSeconds,
		false
	);
}

void USGPlayerCharacterLanternComponent::ToggleLanternModes()
{
	if (bLanternActive == false) { return; }

	bUVIsActive = !bUVIsActive;

	if(bUVIsActive == false)
	{
		AudioComponent->Sound = UVDisableSound;
		NormalLantern();
	}
	else
	{
		AudioComponent->Sound = UVEnableSound;
		UVLantern();
	}

	UVEnabledChanged.Broadcast(bUVIsActive);
	if (AudioComponent->Sound != nullptr)
	{
		AudioComponent->Play();
	}
}

void USGPlayerCharacterLanternComponent::ToggleLantern()
{
	bLanternActive = !bLanternActive;

	if (bLanternActive)
	{
		AudioComponent->Sound = LanternEnableSound;
		Lantern->SetIntensity(LightIntensity);
	}
	else
	{
		AudioComponent->Sound = LanternDisableSound;
		Lantern->SetIntensity(0.f);
	}

	LanternEnabledChanged.Broadcast(bLanternActive);
	if (AudioComponent->Sound != nullptr)
	{
		AudioComponent->Play();
	}
}

void USGPlayerCharacterLanternComponent::UVLantern()
{
	SetBatteryTime(UVBatteryDrainTime);

	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(UVColor);

}

void USGPlayerCharacterLanternComponent::NormalLantern()
{
	SetBatteryTime(NormalBatteryDrainTime);

	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(NormalColor);
}

void USGPlayerCharacterLanternComponent::ChargeLantern()
{
	CurrentBattery = BatteryMax;

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "FULLY CHARGED");
}