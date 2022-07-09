// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AGCEPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ANDREIGRBCODEEXAMPLE_API AAGCEPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AAGCEPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TPCamera = nullptr;
	
private:
	UFUNCTION()
	void GamepadTurn(const float Value);
	
	UFUNCTION()
	void GamepadLookUp(const float Value);

	UFUNCTION()
	void MouseTurn(const float Value);

	UFUNCTION()
	void MouseLookUp(const float Value);

private:
	UPROPERTY(EditDefaultsOnly)
	float GamepadBaseTurnRate = 45.f;

	UPROPERTY(EditDefaultsOnly)
	float GamepadBaseLookUpRate = 22.5f;

	UPROPERTY(EditDefaultsOnly)
	float MouseBaseTurnRate = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float MouseBaseLookUpRate = 1.f;

private:
	UFUNCTION()
	void MoveForward(const float Value);

	UFUNCTION()
	void MoveRight(const float Value);

private:
	UFUNCTION()
	void JumpPressed();

	UFUNCTION()
	void JumpReleased();
};
