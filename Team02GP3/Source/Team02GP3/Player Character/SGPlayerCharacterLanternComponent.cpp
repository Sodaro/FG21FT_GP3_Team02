#include "SGPlayerCharacterLanternComponent.h"
#include "Components/AudioComponent.h"


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

}

void USGPlayerCharacterLanternComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DecreaseBattery(DeltaTime);

	SwitchingLights(DeltaTime);
}

void USGPlayerCharacterLanternComponent::SetupLanternValues()
{
	SetBatteryTime(NormalBatteryDrainTime);

	LightIntensity = Lantern->Intensity;
	LightIntensitySAVED = LightIntensity;
	UVIntensity = LightIntensity;
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
	if (bUVIsActive)
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
	
	if (CurrentBattery >= 20.f)
	{
		// 100% - 20% HighCharger, Normal Intensity and Range
		LightIntensity = LightIntensitySAVED;
		bLowBattery = false;
		bNoBatteryLeft = false;
	}
	if (CurrentBattery > 0.f && CurrentBattery <= 19.f)
	{
		// 19% - 1% LowCharge, Decreased Intensity and Range + Flickering 
		bLowBattery = true;
		bNoBatteryLeft = false;
		LightFlickering();
	}
	if (CurrentBattery <= 0.f)
	{
		// 0% No UV
		NormalLantern();
		bNoBatteryLeft = true;
	}
}

void USGPlayerCharacterLanternComponent::LightFlickering()
{
	if (bLowBattery == false || CurrentBattery <= 0 || bUVIsActive == false) { return; }

	float RandomSeconds = FMath::RandRange(1.f,2.f);
	float WaitForSeconds =2.f;

	float RandomStrongIntensity = FMath::RandRange(LowerIntensity - 200.f, LowerIntensity);
	float RandomWeakIntensity = FMath::RandRange(LowerIntensity - 4000.f, LowerIntensity - 2000.f);

	switch (LightFlickeringCase)
	{
	case 0:
		// Stronger light
		SetLightIntensity(RandomStrongIntensity); 
		WaitForSeconds = RandomSeconds;
		UVIntensity = RandomStrongIntensity;

		LightFlickeringCase++;
		break;
	case 1:
		// Weaker light
		SetLightIntensity(RandomWeakIntensity); 
		WaitForSeconds = RandomSeconds;
		UVIntensity = RandomWeakIntensity;

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

void USGPlayerCharacterLanternComponent::UVLantern()
{
	if (bNoBatteryLeft) { return; }

	SetBatteryTime(UVBatteryDrainTime);

	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(UVColor);

	SetLightIntensity(UVIntensity);

	bUVIsActive = true;
	if (UVEnableSound != nullptr)
	{
		AudioComponent->Sound = UVEnableSound;
		AudioComponent->Play();
	}
	UVEnabledChanged.Broadcast(true);
}

void USGPlayerCharacterLanternComponent::NormalLantern()
{
	TimeBeforeChangingLight = TimeBeforeChangeKeeper;

	Lantern->SetLightColor(NormalColor);

	SetLightIntensity(LightIntensitySAVED);

	bUVIsActive = false;
	if (UVDisableSound != nullptr)
	{
		AudioComponent->Sound = UVDisableSound;
		AudioComponent->Play();
	}
	UVEnabledChanged.Broadcast(false);
}

void USGPlayerCharacterLanternComponent::ChargeLantern()
{
	CurrentBattery = BatteryMax;
	bNoBatteryLeft = false;
}