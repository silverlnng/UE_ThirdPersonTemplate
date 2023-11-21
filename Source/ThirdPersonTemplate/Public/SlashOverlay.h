// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlashOverlay.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API USlashOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthBarPercent (float percent);
	void SetGoldText(FString text);
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* healthProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* staminaProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* goldText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* soulsText;
	
};
