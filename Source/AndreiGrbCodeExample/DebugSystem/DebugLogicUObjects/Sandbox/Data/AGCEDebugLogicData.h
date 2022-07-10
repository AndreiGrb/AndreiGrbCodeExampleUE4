// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugLogic.h"
#include "AGCEDebugLogicData.generated.h"

UENUM(BlueprintType)
enum class EDebugDataType : uint8
{
	DATA_FPS UMETA(DisplayName = "FPS"),
	DATA_PING UMETA(DisplayName = "Ping")
};

/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugLogicData : public UAGCEDebugLogic, public FTickableGameObject
{
	GENERATED_BODY()

protected:
	virtual bool IsTickable() const override { return true; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual TStatId GetStatId() const override { return TStatId(); }
	virtual UWorld* GetWorld() const override { return GetOuter()->GetWorld(); }

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void InitLogic_Implementation() override;

	virtual void ActivateDebugLogic_Implementation() override;

	virtual void DeactivateDebugLogic_Implementation() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	FText FormatIncomingFloat(const float IncomingFloat);

private:
	float DeltaSeconds = 0.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDebugDataType DataType = EDebugDataType::DATA_FPS;

	UPROPERTY(BlueprintReadOnly)
	FText DefaultText = FText();

	UPROPERTY(BlueprintReadOnly)
	bool bIsTextBlockValid = false;

private:
	UFUNCTION()
	void UpdateText();

	FTimerHandle UpdateTextTimer;

	UPROPERTY(EditAnywhere)
	float TimerTime = .1f;
};
