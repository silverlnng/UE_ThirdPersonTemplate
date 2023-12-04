// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayer1.h"

void UMainGameInstance::PullPlayerMoney()
{
	ATPSPlayer1* myplayer = Cast<ATPSPlayer1>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(myplayer)
	{
		myplayer->money=playerMoney;
	}
}

void UMainGameInstance::PushPlayerMoney()
{
	ATPSPlayer1* myplayer = Cast<ATPSPlayer1>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(myplayer)
	{
		playerMoney=myplayer->money;
	}
}
