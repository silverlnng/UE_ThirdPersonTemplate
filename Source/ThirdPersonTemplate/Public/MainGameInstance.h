// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player")
	int64 playerMoney;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player")
	TMap<FName,int> playerItems;
	
	UFUNCTION(BlueprintCallable)
	void PullPlayerMoney();
	UFUNCTION(BlueprintCallable)
	void PushPlayerMoney();
};