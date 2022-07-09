// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGCESanboxGM.generated.h"

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCESanboxGM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
