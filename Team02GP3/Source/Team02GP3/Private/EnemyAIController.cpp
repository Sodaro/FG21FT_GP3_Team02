// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController()
{

}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    //UE_LOG(LogTemp, Warning, );
    FName name = Actor->GetFName();
    UE_LOG(LogTemp, Warning, TEXT("plyaer actor name: %s"), *name.ToString());

    if (GetPawn() != nullptr)
    {
        FName PlayerName = GetPawn()->GetFName();
        UE_LOG(LogTemp, Warning, TEXT("enemy pawn name: %s"), *PlayerName.ToString());
    }
    
    if (GetPawn()->GetOwner() != nullptr)
    {
        FName PlayerName = GetPawn()->GetOwner()->GetFName();
        UE_LOG(LogTemp, Warning, TEXT("enemy actor name: %s"), *PlayerName.ToString());
    }

    
    if (Actor->ActorHasTag(FName(TEXT("Player"))))
    {
        UE_LOG(LogTemp, Warning, TEXT("Detect Player"));
        if (BlackboardComp == nullptr)
        {
            BlackboardComp = GetBlackboardComponent();
        }

        if (Stimulus.WasSuccessfullySensed())
        {
            //Stimulus was just found.
            BlackboardComp->SetValueAsObject("Player", Actor);
            BlackboardComp->SetValueAsBool("HasSightOfPlayer", true);
            //BlackboardComp->SetValueAsVector("PlayerLastLocation", Actor->GetActorLocation());
            //CharMoveComp->MaxWalkSpeed = 400.f;
            return;
        }

        //Stimulus was lost
        BlackboardComp->ClearValue("Player");
        BlackboardComp->ClearValue("HasSightOfPlayer");
        BlackboardComp->SetValueAsBool("HasSightOfPlayer", false);
        BlackboardComp->SetValueAsVector("PlayerLastLocation", Actor->GetActorLocation());
        //CharMoveComp->MaxWalkSpeed = 100.f;
    }
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	BlackboardComp = GetBlackboardComponent();
	PerceptionComp = GetPerceptionComponent();
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
    CharMoveComp = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
}
