// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashOverlay.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthBarPercent(float percent)
{
	if(healthProgressBar)
	{
		healthProgressBar->SetPercent(percent);
	}
}

void USlashOverlay::SetGoldText(FString text)
{
	if(goldText)
	{
		FText ftext = FText::FromString(text);
		goldText->SetText(ftext);
	}
}
