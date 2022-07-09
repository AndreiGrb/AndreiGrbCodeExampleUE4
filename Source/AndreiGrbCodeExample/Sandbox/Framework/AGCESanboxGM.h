// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGCESanboxGM.generated.h"

class AAGCEPlayerStartZone;

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCESanboxGM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	void SpawnNewPlayer(APlayerController* NewPlayer);

	FTransform GetSpawnPointFromStartingZone() const;

	FTransform GetSpawnPointFromActor(const AActor* _Actor) const;

private:
	UPROPERTY()
	TArray<APlayerController*> PlayerControllers = {};
	
	UPROPERTY()
	TArray<AAGCEPlayerStartZone*> PlayerStartingZones = {};
};
