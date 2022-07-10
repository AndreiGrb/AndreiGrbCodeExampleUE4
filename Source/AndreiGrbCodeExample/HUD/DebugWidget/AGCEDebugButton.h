// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AndreiGrbCodeExample/DebugSystem/Structures/AGCEDebugButtonStruct.h"
#include "AGCEDebugButton.generated.h"

class UAGCEDebugScrollBox;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugButton : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Button_Debug = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* Text_DebugName = nullptr;

public:
	FORCEINLINE UButton* GetDebugButton() const { return Button_Debug; }

	FORCEINLINE UTextBlock* GetDebugNameText() const { return Text_DebugName; }

private:
	FDebugButtonStruct ButtonStructure;

	bool bIsInitialized = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugLogic* DebugLogic = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugScrollBox* ParentScrollBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugScrollBox* CreatedSubcatScrollBox = nullptr;

public:
	FORCEINLINE UAGCEDebugScrollBox* GetParentScrollBox() const { return ParentScrollBox; }

	FORCEINLINE FDebugButtonStruct GetButtonStructure() const { return ButtonStructure; }

	FORCEINLINE UAGCEDebugLogic* GetDebugLogic() const { return DebugLogic; }

	FORCEINLINE UAGCEDebugScrollBox* GetCreatedSubcatScrollBox() const { return CreatedSubcatScrollBox; }

public:
	void InitButton(const FDebugButtonStruct Struct, UAGCEDebugScrollBox* InParentScrollBox);

	UFUNCTION()
	void PressButton();

public:
	TArray<UAGCEDebugButton*> GetOtherButtonsInSameCat();

	TArray<UAGCEDebugButton*> GetOtherRadioButtonsInSameCat();

	TArray<UAGCEDebugButton*> GetOtherPressedRadioButtInSameCat();

private:
	bool bIsPressed = false;

public:
	void SetPressedState(const bool NewIsPressed);

	FORCEINLINE bool IsPressed() const { return bIsPressed; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetButtonPressedState(const bool NewIsPressed);
};
