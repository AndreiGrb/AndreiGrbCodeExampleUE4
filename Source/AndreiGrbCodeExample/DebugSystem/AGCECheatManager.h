// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "AGCECheatManager.generated.h"

class UAGCEDebugWidget;
/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCECheatManager : public UCheatManager
{
	GENERATED_BODY()

protected:
	virtual void InitCheatManager() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAGCEDebugWidget> DebugButtonClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AActor> DebugRPCActorClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<APlayerController> PlayerControllerForRPC = nullptr;

	UPROPERTY(EditAnywhere)
	int32 DebugWidgetZOrder = 100;

public:
	UFUNCTION()
	void CreateDebugWidget();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugWidget* DebugButtonWidget = nullptr;

public:
	FORCEINLINE UAGCEDebugWidget* GetDebugButtonWidget() const { return DebugButtonWidget; }
};
