// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGCESandboxPC.generated.h"

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCESandboxPC : public APlayerController
{
	GENERATED_BODY()

public:
	AAGCESandboxPC();

protected:
	virtual void BeginPlay() override;
};
