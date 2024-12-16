// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAIController.h"
#include "Kismet/GameplayStatics.h"

void ATPSAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);
}
