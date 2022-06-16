#include "SGChargingStation.h"
#include "Team02GP3/Player/SGPlayer.h"

ASGChargingStation::ASGChargingStation()
{
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));

	Light->SetLightColor(FColor::Green);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	BoxCollider->SetCollisionProfileName(TEXT("Trigger"));

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASGChargingStation::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ASGChargingStation::OnOverlapEnd);

}

void ASGChargingStation::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap Begin"));

		if (ASGPlayer* Player = Cast<ASGPlayer>(OtherActor))
		{
			Player->HandleCharging();
		}
	}
}

void ASGChargingStation::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
		
		if (USGPlayerLantern* Player = Cast<USGPlayerLantern>(OtherActor))
		{

		}
	}
}

void ASGChargingStation::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->SetWorldLocation(this->GetActorLocation());
}
