#include "SGCheckpoint.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Player Character/SGPlayerCharacter.h"



ASGCheckpoint::ASGCheckpoint()
{

	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASGCheckpoint::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASGCheckpoint::OnOverlapEnd);
}


void ASGCheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (hasEntered == false)
	//{
	//	if (OtherActor->IsA<ASGPlayerCharacter>())
	//	{
	//		hasEntered = true;
	//		Cast<ASGPlayerCharacter>(OtherActor)->SaveGame();
	//	}
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "In Box:)");

}

void ASGCheckpoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Out of Box :)");
}


