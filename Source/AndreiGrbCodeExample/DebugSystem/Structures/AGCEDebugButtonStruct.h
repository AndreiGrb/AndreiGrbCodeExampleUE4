// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndreiGrbCodeExample/DebugSystem/Enums/AGCEDebugButtonType.h"
#include "Engine/DataTable.h"
#include "AGCEDebugButtonStruct.generated.h"

class UAGCEDebugLogic;
/**
 *
 */
USTRUCT(BlueprintType)
struct ANDREIGRBCODEEXAMPLE_API FDebugButtonStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EDebugButtonType ButtonType = EDebugButtonType::BUTTON_SUBCAT;

	//Will only work when DebugButtonType is set to Subcat! Otherwise does nothing
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> SubcategoryButtons = nullptr;

	//Logic for debug when initialized and button pressed. Can be left as NULL if no logic needed
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAGCEDebugLogic> ButtonLogic = nullptr;
};