// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AndreiGrbCodeExample/DebugSystem/Structures/AGCEDebugButtonStruct.h"
#include "AGCEDebugScrollBox.generated.h"

class UAGCEDebugWidget;
class UScrollBox;
class UAGCEDebugButton;
class UDataTable;
/**
 * 
 */
UCLASS()
class ANDREIGRBCODEEXAMPLE_API UAGCEDebugScrollBox : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UAGCEDebugButton*> ChildDebugButtons;

	int32 HorizontalBoxOrder = -1;

	bool bIsAlreadyInitialized = false;

public:
	FORCEINLINE TArray<UAGCEDebugButton*> GetChildDebugButtons() const { return ChildDebugButtons; }

	FORCEINLINE int32 GetHorizontalBoxOrder() const { return HorizontalBoxOrder; }

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UScrollBox* ScrollBox_ForButtons = nullptr;

public:
	UAGCEDebugButton* CreateDebugButton(const FText ButtonText, const FDebugButtonStruct ButtonStruct);

	void InitializeScrollBox(const int32 HBoxOrder, UDataTable* ButtonsDataTable,
	                         UAGCEDebugWidget* SetParentDebugWidget, UAGCEDebugScrollBox* SetParentScrollBox);

	void ClearNextInLineSubcats();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugWidget* ParentDebugWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAGCEDebugScrollBox* ParentScrollBox = nullptr;

public:
	FORCEINLINE UAGCEDebugWidget* GetParentDebugWidget() const { return ParentDebugWidget; }
	FORCEINLINE UAGCEDebugScrollBox* GetParentScrollBox() const { return ParentScrollBox; }

public:
	UPROPERTY()
	UAGCEDebugButton* CurrentlySelectedSubcat = nullptr;
};
