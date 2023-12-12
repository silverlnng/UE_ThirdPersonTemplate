// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ObserverInterface.h"
#include "Goblin.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API AGoblin : public AEnemy , public IObserverInterface
{
	GENERATED_BODY()
public:
	AGoblin();

	virtual void Attack_Implementation() override;
	virtual void Defend_Implementation() override;

	//IObserverInterface 의 가상함수를 구현
	virtual void NotifyAttack() override;

	//옵저버 등록 및 알림전달 함수
	void RegisterObserver(IObserverInterface* Observer);
	
	void UnRegisterObserver(IObserverInterface* Observer);

private:
	TArray<IObserverInterface*> observers;

	
	
};
