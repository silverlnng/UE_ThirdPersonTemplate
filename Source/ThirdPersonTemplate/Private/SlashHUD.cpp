// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashHUD.h"
#include "SlashOverlay.h"
#include "Blueprint/UserWidget.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World =GetWorld();

	if(World)
	{
		APlayerController* controller =  World->GetFirstPlayerController();	//�̱��÷��̿����� ���� 1���� ��Ʈ�ѷ��� ����
		if(controller && SlashOverlayClass)
		{
			SlashOverlay = CreateWidget<USlashOverlay>(controller, SlashOverlayClass);
			SlashOverlay->AddToViewport();
		}
	}
	
	
}
