// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "AGCEPlayerStartZone.generated.h"

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCEPlayerStartZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	AAGCEPlayerStartZone();

public:
	UFUNCTION(BlueprintCallable)
	FVector GetRandomSpawnPointInZone() const;
};