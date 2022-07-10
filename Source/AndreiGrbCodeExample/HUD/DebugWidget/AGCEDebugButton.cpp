// Fill out your copyright notice in the Description page of Project Settings.


#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugButton.h"

#include "AGCEDebugScrollBox.h"
#include "AGCEDebugWidget.h"
#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugLogic.h"
#include "Components/Button.h"

void UAGCEDebugButton::InitButton(const FDebugButtonStruct Struct, UAGCEDebugScrollBox* InParentScrollBox)
{
	if (bIsInitialized)
	{
		return;
	}

	bIsInitialized = true;
	ButtonStructure = Struct;
	ParentScrollBox = InParentScrollBox;

	Button_Debug->OnClicked.AddDynamic(this, &UAGCEDebugButton::PressButton);

	if(Struct.ButtonLogic)
	{
		const bool bIsDebugAlreadyActive = ParentScrollBox->GetParentDebugWidget()->IsDebugActive(Struct.ButtonLogic);
		if (bIsDebugAlreadyActive)
		{
			SetPressedState(true);

			DebugLogic = ParentScrollBox->GetParentDebugWidget()->GetActiveDebug(Struct.ButtonLogic);
			DebugLogic->ParentDebugButton = this;
			DebugLogic->Init(this);
		}
		else
		{
			DebugLogic = NewObject<UAGCEDebugLogic>(this, Struct.ButtonLogic);
			DebugLogic->Init(this);
		}
	}
}

void UAGCEDebugButton::PressButton()
{
	switch(ButtonStructure.ButtonType)
	{
		case EDebugButtonType::BUTTON_SUBCAT:
		{
				//stop all logic if press state is already TRUE
			if (bIsPressed)
			{
				return;
			}

				//set press state to TRUE
			SetPressedState(true);

				//create list of buttons from this SubCategory
			ParentScrollBox->ClearNextInLineSubcats();
			ParentScrollBox->CurrentlySelectedSubcat = this;
			CreatedSubcatScrollBox = ParentScrollBox->GetParentDebugWidget()->CreateNextButtonList(ButtonStructure.SubcategoryButtons.LoadSynchronous());

				//trigger debug logic (If there is one for SubCategory button. Usually there is none)
			if (DebugLogic)
			{
				DebugLogic->ButtonPressed();
			}

				//set other SubCategory buttons in the same category press state to false
				//AND deactivate debug(If there is one for SubCategory button. Usually there is none)
			TArray<UAGCEDebugButton*> OtherDebugButtons = GetOtherButtonsInSameCat();
			for(UAGCEDebugButton* DebugButton : OtherDebugButtons)
			{
				if(DebugButton->GetButtonStructure().ButtonType == EDebugButtonType::BUTTON_SUBCAT)
				{
					DebugButton->SetPressedState(false);

					if (DebugButton->GetDebugLogic())
					{
						DebugButton->GetDebugLogic()->DeactivateDebug();
					}
				}
			}

			break;
		}

		case EDebugButtonType::BUTTON_REGULAR:
		{
				//trigger debug logic
			if (DebugLogic)
			{
				DebugLogic->ButtonPressed();
			}

			break;
		}

		case EDebugButtonType::BUTTON_RADIO:
		{
				//stop all logic if press state is already TRUE
			if (bIsPressed)
			{
				return;
			}

				//set press state to TRUE
			SetPressedState(true);

				//trigger debug logic
			if (DebugLogic)
			{
				DebugLogic->ButtonPressed();
			}

				//set other radio buttons press state to false AND deactivate debug
			TArray<UAGCEDebugButton*> OtherRadioButtons = GetOtherRadioButtonsInSameCat();
			for(UAGCEDebugButton* RadioDebugButton : OtherRadioButtons)
			{
				RadioDebugButton->SetPressedState(false);

				if (RadioDebugButton->GetDebugLogic())
				{
					RadioDebugButton->GetDebugLogic()->DeactivateDebug();
				}
			}

			break;
		}

		case EDebugButtonType::BUTTON_RADIOTOGGLE:
		{
				//toggle press state
			SetPressedState(!bIsPressed);

				//trigger debug logic
			if (DebugLogic)
			{
				DebugLogic->ButtonPressed();
			}

				//set other radio buttons press state to false AND deactivate debug
			TArray<UAGCEDebugButton*> OtherRadioButtons = GetOtherRadioButtonsInSameCat();
			for (UAGCEDebugButton* RadioDebugButton : OtherRadioButtons)
			{
				RadioDebugButton->SetPressedState(false);

				if(RadioDebugButton->GetDebugLogic())
				{
					RadioDebugButton->GetDebugLogic()->DeactivateDebug();
				}
			}

			break;
		}

		case EDebugButtonType::BUTTON_TOGGLE:
		{
				//toggle press state
			SetPressedState(!bIsPressed);

				//trigger debug logic
			if (DebugLogic)
			{
				DebugLogic->ButtonPressed();
			}

			break;
		}

		case EDebugButtonType::BUTTON_HIDDEN:
		{
			break;
		}
	}
}

TArray<UAGCEDebugButton*> UAGCEDebugButton::GetOtherButtonsInSameCat()
{
	TArray<UAGCEDebugButton*> DebugButtonsInScrollBox = ParentScrollBox->GetChildDebugButtons();
	DebugButtonsInScrollBox.Remove(this);

	return DebugButtonsInScrollBox;
}

TArray<UAGCEDebugButton*> UAGCEDebugButton::GetOtherRadioButtonsInSameCat()
{
	TArray<UAGCEDebugButton*> OtherRadioButtons;

	TArray<UAGCEDebugButton*> OtherDebugButtons = GetOtherButtonsInSameCat();
	for (UAGCEDebugButton* DebugButton : OtherDebugButtons)
	{
		const EDebugButtonType DebugButtonType = DebugButton->GetButtonStructure().ButtonType;
		if (DebugButtonType == EDebugButtonType::BUTTON_RADIO || DebugButtonType == EDebugButtonType::BUTTON_RADIOTOGGLE)
		{
			OtherRadioButtons.Add(DebugButton);
		}
	}

	return OtherRadioButtons;
}

TArray<UAGCEDebugButton*> UAGCEDebugButton::GetOtherPressedRadioButtInSameCat()
{
	TArray<UAGCEDebugButton*> OtherPressedRadioButtons;

	TArray<UAGCEDebugButton*> OtherRadioDebugButtons = GetOtherRadioButtonsInSameCat();
	for(UAGCEDebugButton* RadioDebugButton : OtherRadioDebugButtons)
	{
		if(RadioDebugButton->IsPressed())
		{
			OtherPressedRadioButtons.Add(RadioDebugButton);
		}
	}

	return OtherPressedRadioButtons;
}

void UAGCEDebugButton::SetPressedState(const bool NewIsPressed)
{
	bIsPressed = NewIsPressed;

	SetButtonPressedState(NewIsPressed);
}
