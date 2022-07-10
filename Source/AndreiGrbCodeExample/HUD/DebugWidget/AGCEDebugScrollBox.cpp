// Fill out your copyright notice in the Description page of Project Settings.


#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugScrollBox.h"
#include "AGCEDebugButton.h"
#include "AGCEDebugWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

UAGCEDebugButton* UAGCEDebugScrollBox::CreateDebugButton(const FText ButtonText, const FDebugButtonStruct ButtonStruct)
{
	if(!ParentDebugWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("UAGCEDebugScrollBox::CreateDebugButton() ParentDebugWidget = nullptr"));
		return nullptr;
	}

	UAGCEDebugButton* CreatedDebugButton = CreateWidget<UAGCEDebugButton>(GetOwningPlayer(), ParentDebugWidget->GetDebugButtonWidgetClass());
	ChildDebugButtons.Add(CreatedDebugButton);
	CreatedDebugButton->GetDebugNameText()->SetText(ButtonText);
	ScrollBox_ForButtons->AddChild(CreatedDebugButton);
	CreatedDebugButton->InitButton(ButtonStruct, this);

	return CreatedDebugButton;
}

void UAGCEDebugScrollBox::InitializeScrollBox(const int32 HBoxOrder, UDataTable* ButtonsDataTable,
                                             UAGCEDebugWidget* SetParentDebugWidget,
                                             UAGCEDebugScrollBox* SetParentScrollBox)
{
	if(bIsAlreadyInitialized)
	{
		return;
	}

	bIsAlreadyInitialized = true;
	HorizontalBoxOrder = HBoxOrder;
	ParentDebugWidget = SetParentDebugWidget;
	ParentScrollBox = SetParentScrollBox;

	if(ButtonsDataTable)
	{
		TArray<FDebugButtonStruct*> ButtonStructs;
		ButtonsDataTable->GetAllRows<FDebugButtonStruct>(FString("Context"), ButtonStructs);

		for (int32 i = 0; i < ButtonStructs.Num(); i++)
		{
			const FDebugButtonStruct Struct = *ButtonStructs[i];

			if (Struct.ButtonType == EDebugButtonType::BUTTON_HIDDEN)
			{
				continue;
			}

			const FName RowName = ButtonsDataTable->GetRowNames()[i];

			CreateDebugButton(FText::FromName(RowName), Struct);
		}
	}
}

void UAGCEDebugScrollBox::ClearNextInLineSubcats()
{
	UHorizontalBox* ParentHBoxPtr = GetParentDebugWidget()->GetDebugButtonsHBox();
	for (int32 i = ParentHBoxPtr->GetChildrenCount() - 1; i > GetHorizontalBoxOrder(); i--)
	{
		ParentHBoxPtr->RemoveChildAt(i);
	}
}
