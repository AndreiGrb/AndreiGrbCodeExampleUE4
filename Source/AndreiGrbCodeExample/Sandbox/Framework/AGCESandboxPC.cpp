// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCESandboxPC.h"

#include "AndreiGrbCodeExample/DebugSystem/AGCEDebugManager.h"


AAGCESandboxPC::AAGCESandboxPC()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void AAGCESandboxPC::BeginPlay()
{
	Super::BeginPlay();

	EnableCheats();
	
	if(IsLocalController())
	{
		if (IsValid(CheatManager))
		{
			if(UAGCEDebugManager* DebugManager = Cast<UAGCEDebugManager>(CheatManager))
			{
				DebugManager->CreateDebugWidget();
			}
		}
		
		SetInputMode(FInputModeGameOnly());
	}
}
