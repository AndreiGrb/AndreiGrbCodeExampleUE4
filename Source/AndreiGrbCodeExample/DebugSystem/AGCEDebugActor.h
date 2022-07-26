// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGCEDebugActor.generated.h"

class UDataTable;

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCEDebugActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAGCEDebugActor();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void LoadDebugLogicListServer(TSoftObjectPtr<UDataTable> DataTableToLoad);
};
