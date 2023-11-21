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
	USlashOverlay* SlashOverlay;	//PRIVATE �������� CHARACTER ���� ����Ҽ�����
	
//inline�� simple getter �̴�.
public:
	FORCEINLINE USlashOverlay* GetSlashOverlay() const {return  SlashOverlay; }
	
};
