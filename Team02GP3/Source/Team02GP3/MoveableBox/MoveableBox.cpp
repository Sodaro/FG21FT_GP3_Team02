#include "MoveableBox.h"
#include "Components/StaticMeshComponent.h"
#include "Team02GP3/Player Character/SGPlayerCharacter.h"

AMoveableBox::AMoveableBox()
{
	PrimaryActorTick.bCanEverTick = true;
	Spherey = CreateDefaultSubobject<USphereComponent>(TEXT("Spherey"));
}

void AMoveableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBeingMoved)
	{
		MoveBox(PlayerActor);
	}
}

void AMoveableBox::HandleBoxInteraction(AActor* OtherActor)
{
	if (bIsBeingMoved)
	{
		DropBox();
	}
	else
	{
		PlayerActor = OtherActor;
		bIsBeingMoved = true;
	}
}

void AMoveableBox::DropBox()
{
	bIsBeingMoved = false;
	FVector Offset = FVector(0.f, 0.f, 100.f);
	SetActorLocation(GetActorLocation());
}

void AMoveableBox::MoveBox(AActor* OtherActor)
{
	FVector PlayerLocation = OtherActor->GetActorLocation();
	FVector NewLocation = (PlayerLocation + (OtherActor->GetActorForwardVector() * 100.f)) - FVector(0.f, 0.f, 40.f);

	SetActorLocation(NewLocation);
}