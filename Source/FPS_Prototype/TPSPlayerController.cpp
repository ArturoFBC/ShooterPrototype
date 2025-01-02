// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ATPSPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UUserWidget* EndGameScreen;
    if (bIsWinner)
    {
        EndGameScreen = CreateWidget(this, WinScreenClass);
    }
    else
    {
        EndGameScreen = CreateWidget(this, LoseScreenClass);
    }

    if (EndGameScreen != nullptr)
    {
        EndGameScreen->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
