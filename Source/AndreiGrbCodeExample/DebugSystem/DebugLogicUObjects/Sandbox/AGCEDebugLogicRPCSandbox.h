// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugLogic.h"
#include "AGCEDebugLogicRPCSandbox.generated.h"

class AAGCEDebugRPCSandboxActor;
/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugLogicRPCSandbox : public UAGCEDebugLogic
{
	GENERATED_BODY()

protected:
	AAGCEDebugRPCSandboxActor* GetRPCActor() const;
};
