// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"
#include "TPSAIController.h"
#include "EngineUtils.h"

void AKillAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (ATPSAIController* Controller : TActorRange<ATPSAIController>(GetWorld()))
    {
        if (Controller->IsDead() == false)
        {
            return;
        }
    }

    EndGame(true);
}

void AKillAllGameMode::EndGame(bool bIsplayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool ThisWon = Controller->IsPlayerController() == bIsplayerWinner;

        Controller->GameHasEnded(Controller->GetPawn(), ThisWon);
    }
}
