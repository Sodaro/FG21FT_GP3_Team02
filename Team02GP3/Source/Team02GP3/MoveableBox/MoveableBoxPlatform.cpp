#include "MoveableBoxPlatform.h"
#include "MoveableBox.h"
#include "MoveableBoxUnlock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Team02GP3/Player Character/SGPlayerCharacter.h"

AMoveableBoxPlatform::AMoveableBoxPlatform()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	BoxCollider->SetCollisionProfileName(TEXT("Trigger"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMoveableBoxPlatform::OnOverlapBegin);
}

void AMoveableBoxPlatform::LockBox(AActor* Box)
{
	Box->SetActorLocation(GetActorLocation());
	bBoxIsLockedIn = true;
}

void AMoveableBoxPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && bBoxIsPlaced == false)
	{
		if (AMoveableBox* Box = Cast<AMoveableBox>(OtherActor))
		{
			LockBox(Box);	
			bBoxIsLockedIn = true;

			Box->Spherey->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
			Box->bIsBeingMoved = false;

			ASGPlayerCharacter* PlayerCharacter = Cast<ASGPlayerCharacter>(Player);
			PlayerCharacter->ResetPlayer();
			
			if (bOnlyCallOnce == true)
			{
				Unlock->CheckTotalLockedBoxes();
				bBoxIsPlaced = true;
				bOnlyCallOnce = false;
			}
		}
	}
}

void AMoveableBoxPlatform::GetUnlock(AActor* BoxUnlock)
{
	Unlock = Cast<AMoveableBoxUnlock>(BoxUnlock);
}
