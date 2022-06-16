// Fill out your copyright notice in the Description page of Project Settings.


#include "SGTriggerBox.h"

#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Team02GP3/Player Character/SGPlayerCharacter.h"

ASGTriggerBox::ASGTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ASGTriggerBox::Event);
}

void ASGTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void ASGTriggerBox::Event(class AActor* OverlappedActor, class AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "In Box:)");
	if (OtherActor && OtherActor != this && Cast<ASGPlayerCharacter>(OtherActor))
	{
		if (Fountain)
		{
			Fountain->FindComponentByClass<UParticleSystemComponent>()->Activate();
		}
	}
}