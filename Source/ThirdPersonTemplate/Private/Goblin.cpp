// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
}

void AGoblin::Attack_Implementation()
{
	//고블린의 공격기능 구현
	UE_LOG(LogTemp,Warning,TEXT("Goblin is attacking"));

	//공격능력을 사용하면 옵저버에게 알림을 보내야한다
	// 옵저버 목록을 for문으로 모두 조회 
	for(IObserverInterface* observer : observers)
	{
		if(observer)
		{
			observer->NotifyAttack();
		}
	}
}

void AGoblin::Defend_Implementation()
{
	// 고블린 적의 방어 기능 구현 
	UE_LOG(LogTemp,Warning,TEXT("Goblin is defending"));
}

void AGoblin::NotifyAttack()
{
	
}

void AGoblin::RegisterObserver(IObserverInterface* Observer)
{
	// 옵저버 등록
	observers.AddUnique(Observer);
}

void AGoblin::UnRegisterObserver(IObserverInterface* Observer)
{
	//옵저버 제거
	observers.Remove(Observer);
}
