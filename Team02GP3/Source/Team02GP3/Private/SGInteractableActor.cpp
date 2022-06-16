#include "SGInteractableActor.h"
#include "Components/SphereComponent.h"
#include "../Player Character/SGPlayerCharacter.h"
#include "SGPlayerInteractionComponent.h"

void ASGInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	InteractionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGInteractableActor::OnInteractionBeginOverlap);
	InteractionSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ASGInteractableActor::OnInteractionEndOverlap);
}

ASGInteractableActor::ASGInteractableActor()
{
	InteractionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionTrigger"));
	InteractionSphereComponent->SetupAttachment(RootComponent);
}
//
void ASGInteractableActor::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	if (bPlayerInZone)
		return;

	if (OtherActor->GetClass()->IsChildOf(PlayerClass))
	{
		auto Player = Cast<ASGPlayerCharacter>(OtherActor);
		auto InteractionComp = Cast<USGPlayerInteractionComponent>(OtherActor->GetComponentByClass(USGPlayerInteractionComponent::StaticClass()));
		OnPlayerOverlapEnter(Player,InteractionComp);
		bPlayerInZone = true;
		PlayerOverlapEnter.Broadcast(Player, InteractionComp);
	}
}

void ASGInteractableActor::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bPlayerInZone == false)
		return;

	if (OtherActor->GetClass()->IsChildOf(PlayerClass))
	{
		auto Player = Cast<ASGPlayerCharacter>(OtherActor);
		auto InteractionComp = Cast<USGPlayerInteractionComponent>(OtherActor->GetComponentByClass(USGPlayerInteractionComponent::StaticClass()));
		OnPlayerOverlapExit(Player, InteractionComp);
		bPlayerInZone = false;
		PlayerOverlapExit.Broadcast(Player, InteractionComp);
	}
}

