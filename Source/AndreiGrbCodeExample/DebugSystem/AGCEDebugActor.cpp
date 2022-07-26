// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugActor.h"


AAGCEDebugActor::AAGCEDebugActor()
{
	//PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void AAGCEDebugActor::BeginPlay()
{
	Super::BeginPlay();
}
