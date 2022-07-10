// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugLogicRPCSandbox.h"

#include "AGCEDebugRPCSandboxActor.h"
#include "Kismet/GameplayStatics.h"

AAGCEDebugRPCSandboxActor* UAGCEDebugLogicRPCSandbox::GetRPCActor() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AAGCEDebugRPCSandboxActor::StaticClass(), OutActors);

	if(OutActors.Num() > 0)
	{
		return Cast<AAGCEDebugRPCSandboxActor>(OutActors[0]);
	}

	return nullptr;
}
