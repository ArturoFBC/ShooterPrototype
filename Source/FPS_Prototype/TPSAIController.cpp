// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAIController.h"
#include "Kismet/GameplayStatics.h"
#include "TPSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATPSAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
    
}

void ATPSAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool ATPSAIController::IsDead() const
{
    ATPSCharacter* ThisCharacter = Cast<ATPSCharacter>(GetPawn());
    if (ThisCharacter != nullptr)
    {
        return ThisCharacter->IsDead();
    }

    return true;
}
