// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlashHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API ASlashHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual  void BeginPlay() override;
private:	
	UPROPERTY(EditDefaultsOnly, Category = Slash)
	TSubclassOf<class USlashOverlay> SlashOverlayClass;

	UPROPERTY()
	USlashOverlay* SlashOverlay;	//PRIVATE 설정으로 CHARACTER 에서 사용할수없음
	
//inline은 simple getter 이다.
public:
	FORCEINLINE USlashOverlay* GetSlashOverlay() const {return  SlashOverlay; }
	
};
