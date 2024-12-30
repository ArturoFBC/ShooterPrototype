// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"

void AKillAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    UE_LOG(LogTemp, Warning, TEXT("%hs"), "BBBB");
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("%hs"), "CCCC");
        PlayerController->GameHasEnded(nullptr, false);
    }
}
