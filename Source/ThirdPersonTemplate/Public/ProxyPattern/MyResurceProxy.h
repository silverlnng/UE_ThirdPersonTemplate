// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyResourceInterface.h"
#include "MyResurceProxy.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UMyResurceProxy : public UObject ,public IMyResourceInterface
{
	GENERATED_BODY()

private:
	class UMyConcreteResource* ActualResource;
public:


	UMyResurceProxy(); 
	virtual void LoadResource() override;
	virtual void UseResource() override;

	~UMyResurceProxy();	//�Ҹ��ڿ��� ���� ���ҽ��� ���� 
};
