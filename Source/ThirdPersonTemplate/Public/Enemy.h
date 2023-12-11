// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API AEnemy : public AUnit
{
	GENERATED_BODY()
public:
	AEnemy();

	//Unit Ŭ���� (�θ�Ŭ����)�� �Լ� ����
	virtual void Attack_Implementation() override;
	virtual void Defend_Implementation() override;
};
