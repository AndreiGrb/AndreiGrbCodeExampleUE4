// Fill out your copyright notice in the Description page of Project Settings.


#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"

#include "AGCEDebugButton.h"
#include "AGCEDebugScrollBox.h"
#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugLogic.h"
#include "AndreiGrbCodeExample/DebugSystem/Structures/AGCEDebugButtonStruct.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UAGCEDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Title->SetVisibility(ESlateVisibility::Hidden);
	Text_FPS->SetVisibility(ESlateVisibility::Hidden);
	Text_Ping->SetVisibility(ESlateVisibility::Hidden);

	FOnInputAction Callback;
	Callback.BindUFunction(this, "ToggleDebugMenu");
	
	ListenForInputAction("ToggleDebugMenu", IE_Pressed, true, Callback);
}

void UAGCEDebugWidget::ToggleDebugMenu()
{
	APlayerController* OwningPlayer = GetOwningPlayer();
	
	//Open menu
	if (HBox_DebugButtons->GetAllChildren().Num() == 0)
	{
		TArray<TSoftClassPtr<APlayerController>> SoftPCClassArray;
		DataTablesForButtons.GetKeys(SoftPCClassArray);

		for (TSoftClassPtr<APlayerController>& SoftPCClass : SoftPCClassArray)
		{
			if (SoftPCClass.Get() == OwningPlayer->GetClass())
			{
				if (TSoftObjectPtr<UDataTable>* SoftDataTable = DataTablesForButtons.Find(SoftPCClass))
				{
					ChosenDataTable = SoftDataTable->LoadSynchronous();
				}
			}
		}

		if (!ChosenDataTable)
		{
			UE_LOG(LogTemp, Error, TEXT("UAGCEDebugManager::InitDebugManager() ChosenDataTable = nullptr"));
			return;
		}

		CreateNextButtonList(ChosenDataTable);
		
		OwningPlayer->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(OwningPlayer, this);

		Text_Title->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{ //Close menu
		RemoveDebugList();

		OwningPlayer->SetShowMouseCursor(false);
		OwningPlayer->SetInputMode(FInputModeGameOnly());

		Text_Title->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAGCEDebugWidget::RemoveDebugList()
{
	for (int32 i = HBox_DebugButtons->GetAllChildren().Num() - 1; i >= 0; i--)
	{
		HBox_DebugButtons->RemoveChildAt(i);
	}
}

UAGCEDebugScrollBox* UAGCEDebugWidget::CreateNextButtonList(UDataTable* Buttons)
{
	if(!ScrollBoxWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UAGCEDebugWidget::CreateNextButtonList() ScrollBoxWidgetClass = nullptr"));
		return nullptr;
	}
	if(!DebugButtonWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UAGCEDebugWidget::CreateNextButtonList() DebugButtonWidgetClass = nullptr"));
		return nullptr;
	}

	UAGCEDebugScrollBox* ScrollBoxWidget = CreateWidget<UAGCEDebugScrollBox>(GetOwningPlayer(), ScrollBoxWidgetClass);
	UHorizontalBoxSlot* ScrollBoxAsSlot = HBox_DebugButtons->AddChildToHorizontalBox(ScrollBoxWidget);

	const int32 HBoxOrder = HBox_DebugButtons->GetChildrenCount() - 1;

	UAGCEDebugScrollBox* ParentScrollBox = nullptr;
	if(HBox_DebugButtons->GetChildrenCount() > 1)
	{
		ParentScrollBox = Cast<UAGCEDebugScrollBox>(HBox_DebugButtons->GetChildAt(HBox_DebugButtons->GetChildrenCount() - 2));
	}

	ScrollBoxWidget->InitializeScrollBox(HBoxOrder, Buttons, this, ParentScrollBox);

	return ScrollBoxWidget;
}

bool UAGCEDebugWidget::IsDebugActive(TSubclassOf<UAGCEDebugLogic> DebugClass) const
{
	return ActiveDebugs.Contains(DebugClass);
}

TArray<UAGCEDebugLogic*> UAGCEDebugWidget::GetAllActiveDebugs() const
{
	TArray<TSubclassOf<UAGCEDebugLogic>> MapKeys;
	ActiveDebugs.GetKeys(MapKeys);

	TArray<UAGCEDebugLogic*> ReturnActiveDebugs = {};

	for(TSubclassOf<UAGCEDebugLogic>& Key : MapKeys)
	{
		ReturnActiveDebugs.Add(*ActiveDebugs.Find(Key));
	}

	return ReturnActiveDebugs;
}

UAGCEDebugLogic* UAGCEDebugWidget::GetActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass) const
{
	return *ActiveDebugs.Find(DebugClass);
}

UAGCEDebugLogic* UAGCEDebugWidget::AddActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass,
                                                UAGCEDebugLogic* DebugLogicPtr)
{
	return ActiveDebugs.Add(DebugClass, DebugLogicPtr);
}

int32 UAGCEDebugWidget::RemoveActiveDebug(TSubclassOf<UAGCEDebugLogic> DebugClass)
{
	return ActiveDebugs.Remove(DebugClass);
}
