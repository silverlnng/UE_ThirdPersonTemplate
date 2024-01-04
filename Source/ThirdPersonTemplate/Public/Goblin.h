// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ObserverPattern/ObserverInterface.h"
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
	//AEnemy 클래스의 가상함수를 오버라이드 하여 구현
	virtual void Attack_Implementation() override;
	virtual void Defend_Implementation() override;

	//IObserverInterface 의 가상함수를 구현
	virtual void NotifyAttack() override;

	//옵저버 등록 및 알림전달 함수
	void RegisterObserver(IObserverInterface* Observer);
	
	void UnRegisterObserver(IObserverInterface* Observer);

private:
	// 옵저버들의 목록
	TArray<IObserverInterface*> observers;

	
	
};
