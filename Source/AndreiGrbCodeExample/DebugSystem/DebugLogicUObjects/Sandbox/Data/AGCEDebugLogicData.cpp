// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugLogicData.h"

#include "Components/TextBlock.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugButton.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugScrollBox.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UAGCEDebugLogicData::Tick(float DeltaTime)
{
	DeltaSeconds = DeltaTime;
}

void UAGCEDebugLogicData::InitLogic_Implementation()
{
	switch (DataType)
	{
		case EDebugDataType::DATA_FPS:
		{
			UTextBlock* FPSTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetFPSText();
			if (!FPSTextBlock)
				return;

			DefaultText = FPSTextBlock->GetText();

			break;
		}
		case EDebugDataType::DATA_PING:
		{
			UTextBlock* PingTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetPingText();
			if (!PingTextBlock)
				return;

			DefaultText = PingTextBlock->GetText();

			break;
		}
	}

	bIsTextBlockValid = true;
}

void UAGCEDebugLogicData::ActivateDebugLogic_Implementation()
{
	if (!bIsTextBlockValid)
		return;

	switch (DataType)
	{
		case EDebugDataType::DATA_FPS:
		{
			UTextBlock* FPSTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetFPSText();
			if (!FPSTextBlock)
				return;

			FPSTextBlock->SetVisibility(ESlateVisibility::Visible);

			break;
		}
		case EDebugDataType::DATA_PING:
		{
			UTextBlock* PingTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetPingText();
			if (!PingTextBlock)
				return;

			PingTextBlock->SetVisibility(ESlateVisibility::Visible);

			break;
		}
	}

	GetWorld()->GetTimerManager().SetTimer(UpdateTextTimer, this, &UAGCEDebugLogicData::UpdateText, TimerTime, true);
}

void UAGCEDebugLogicData::DeactivateDebugLogic_Implementation()
{
	if (!bIsTextBlockValid)
		return;

	switch (DataType)
	{
		case EDebugDataType::DATA_FPS:
		{
			UTextBlock* FPSTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetFPSText();
			if (!FPSTextBlock)
				return;

			FPSTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			FPSTextBlock->SetText(DefaultText);

			break;
		}
		case EDebugDataType::DATA_PING:
		{
			UTextBlock* PingTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetPingText();
			if (!PingTextBlock)
				return;

			PingTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			PingTextBlock->SetText(DefaultText);

			break;
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(UpdateTextTimer);
}

FText UAGCEDebugLogicData::FormatIncomingFloat_Implementation(const float IncomingFloat)
{
	return FText::FromString(TEXT("TEXTNULL"));
}

void UAGCEDebugLogicData::UpdateText()
{
	switch (DataType)
	{
		case EDebugDataType::DATA_FPS:
		{
			UTextBlock* FPSTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetFPSText();
			if (!FPSTextBlock || DeltaSeconds == 0.f)
				return;

			const FText FPSNewText = FormatIncomingFloat(1.f / DeltaSeconds);
			FPSTextBlock->SetText(FPSNewText);

			break;
		}
		case EDebugDataType::DATA_PING:
		{
			UTextBlock* PingTextBlock = ParentDebugButton->GetParentScrollBox()->GetParentDebugWidget()->GetPingText();
			if (!PingTextBlock)
				return;

			const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (const APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>())
			{
				const FText PingNewText = FormatIncomingFloat(PlayerState->GetPing());
				PingTextBlock->SetText(PingNewText);
			}

			break;
		}
	}
}
