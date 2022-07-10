// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCESandboxPC.h"

#include "AndreiGrbCodeExample/DebugSystem/AGCECheatManager.h"


AAGCESandboxPC::AAGCESandboxPC()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void AAGCESandboxPC::BeginPlay()
{
	Super::BeginPlay();

	EnableCheats();

	if (IsValid(CheatManager) && IsLocalController())
	{
		UAGCECheatManager* AGCECheatManager = Cast<UAGCECheatManager>(CheatManager);
		AGCECheatManager->CreateDebugWidget();
	}
}
