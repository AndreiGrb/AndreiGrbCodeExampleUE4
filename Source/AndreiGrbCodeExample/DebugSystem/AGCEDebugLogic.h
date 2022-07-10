// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGCEDebugLogic.generated.h"

class UAGCEDebugButton;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(ShowWorldContextPin))
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugLogic : public UObject
{
	GENERATED_BODY()

public:
	void Init(UAGCEDebugButton* InParentDebugButton);

	void ButtonPressed();

	void ActivateDebug();

	void DeactivateDebug();

protected:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitLogic();
	virtual void InitLogic_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ButtonPressLogic();
	virtual void ButtonPressLogic_Implementation(); 

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivateDebugLogic();
	virtual void ActivateDebugLogic_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeactivateDebugLogic();
	virtual void DeactivateDebugLogic_Implementation();

	virtual UWorld* GetWorld() const override;

private:
	bool bIsInitialized = false;

	bool bIsDebugActive = false;

public:
	UPROPERTY(BlueprintReadOnly)
	UAGCEDebugButton* ParentDebugButton = nullptr;

protected:
	void FlagThisDebugAsActive(const bool bIsActive);

public:
	FORCEINLINE bool IsDebugActive() const { return bIsDebugActive; }
};
