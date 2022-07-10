// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugLogic.h"
#include "AGCEDebugChangeMap.generated.h"

/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugChangeMap : public UAGCEDebugLogic
{
	GENERATED_BODY()

protected:
	virtual void ButtonPressLogic_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> Level = nullptr;
};
