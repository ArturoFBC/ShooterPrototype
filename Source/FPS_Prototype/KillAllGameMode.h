// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSGameModeBase.h"
#include "KillAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROTOTYPE_API AKillAllGameMode : public ATPSGameModeBase
{
	GENERATED_BODY()

public:
	void PawnKilled(APawn* PawnKilled) override;
};
