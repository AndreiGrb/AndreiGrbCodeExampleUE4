// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugLogic.h"

#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugButton.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugScrollBox.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"
#include "Kismet/GameplayStatics.h"

void UAGCEDebugLogic::Init(UAGCEDebugButton* InParentDebugButton)
{
	if(bIsInitialized)
	{
		return;
	}

	bIsInitialized = true;
	ParentDebugButton = InParentDebugButton;

	InitLogic();
}

void UAGCEDebugLogic::ButtonPressed()
{
	ButtonPressLogic();

	if (ParentDebugButton->IsPressed() && ParentDebugButton->GetButtonStructure().ButtonType != EDebugButtonType::BUTTON_REGULAR)
	{
		ActivateDebug();
	}
	else if(bIsDebugActive)
	{
		DeactivateDebug();
	}
}

void UAGCEDebugLogic::ActivateDebug()
{
	if(!bIsDebugActive)
	{
		FlagThisDebugAsActive(true);

		if(bIsDebugActive)
		{
			ActivateDebugLogic();
		}
	}
}

void UAGCEDebugLogic::DeactivateDebug()
{
	if(bIsDebugActive)
	{
		FlagThisDebugAsActive(false);

		if (!bIsDebugActive)
		{
			DeactivateDebugLogic();
		}
	}
}

void UAGCEDebugLogic::InitLogic_Implementation()
{
	//Init logic (called when button for this logic is created), if needed
}

void UAGCEDebugLogic::ButtonPressLogic_Implementation()
{
	//Logic when button is pressed (not activated by toggle or radio), if needed
}

void UAGCEDebugLogic::ActivateDebugLogic_Implementation()
{
	//Logic when button is activated via radio or toggle option, if needed
}

void UAGCEDebugLogic::DeactivateDebugLogic_Implementation()
{
	//Logic when button is deactivated via radio or toggle option, if needed
}

UWorld* UAGCEDebugLogic::GetWorld() const
{
	if (GIsEditor && !GIsPlayInEditorWorld)
		return nullptr; 
	else if (GetOuter())
		return GetOuter()->GetWorld();
	else
		return nullptr;
}

void UAGCEDebugLogic::FlagThisDebugAsActive(const bool bIsActive)
{
	if(!ParentDebugButton || ParentDebugButton->GetButtonStructure().ButtonType == EDebugButtonType::BUTTON_SUBCAT)
	{
		return;
	}

	TSubclassOf<UAGCEDebugLogic> LogicClass = ParentDebugButton->GetButtonStructure().ButtonLogic;
	UAGCEDebugWidget* DebugWidget = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget();

	bIsDebugActive = bIsActive;

	if(bIsDebugActive)
	{
		DebugWidget->AddActiveDebug(LogicClass, this);
	}
	else
	{
		DebugWidget->RemoveActiveDebug(LogicClass);
	}
}
