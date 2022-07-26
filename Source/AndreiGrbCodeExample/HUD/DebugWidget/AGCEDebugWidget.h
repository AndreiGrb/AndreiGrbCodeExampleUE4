// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGCEDebugWidget.generated.h"

class UTextBlock;
class UAGCEDebugLogic;
class UAGCEDebugScrollBox;
class UHorizontalBox;
class UAGCEDebugButton;
class UDataTable;
/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void ToggleDebugMenu();

	void RemoveDebugList();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* Text_Title = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UHorizontalBox* HBox_DebugButtons = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* Text_FPS = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* Text_Ping = nullptr;

public:
	FORCEINLINE UHorizontalBox* GetDebugButtonsHBox() const { return HBox_DebugButtons; }
	FORCEINLINE UTextBlock* GetFPSText() const { return Text_FPS; }
	FORCEINLINE UTextBlock* GetPingText() const { return Text_Ping; }

public:
	UAGCEDebugScrollBox* CreateNextButtonList(UDataTable* Buttons);

private:
	UPROPERTY(EditAnywhere)
	TMap<TSoftClassPtr<APlayerController>, TSoftObjectPtr<UDataTable>> DataTablesForButtons;

	UPROPERTY()
	UDataTable* ChosenDataTable = nullptr;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAGCEDebugScrollBox> ScrollBoxWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAGCEDebugButton> DebugButtonWidgetClass = nullptr;

public:
	FORCEINLINE TSubclassOf<UAGCEDebugButton> GetDebugButtonWidgetClass() const { return DebugButtonWidgetClass; }

	UFUNCTION(BlueprintCallable)
	bool IsDebugActive(const TSubclassOf<UAGCEDebugLogic> DebugClass) const;

	UFUNCTION(BlueprintCallable)
	TArray<UAGCEDebugLogic*> GetAllActiveDebugs() const;

	UFUNCTION(BlueprintCallable)
	UAGCEDebugLogic* GetActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass) const;

	UFUNCTION(BlueprintCallable)
	UAGCEDebugLogic* AddActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass, UAGCEDebugLogic* DebugLogicPtr);

	UFUNCTION(BlueprintCallable)
	int32 RemoveActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass);

private:
	UPROPERTY()
	TMap<TSubclassOf<UAGCEDebugLogic>, UAGCEDebugLogic*> ActiveDebugs = {};
};
