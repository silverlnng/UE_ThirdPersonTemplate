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
	UE_LOG(LogTemp,Warning,TEXT("Goblin is defending"));
}

void AGoblin::NotifyAttack() override
{
	
}

void AGoblin::RegisterObserver(IObserverInterface* Observer)
{
	observers.AddUnique(Observer);
}

void AGoblin::UnRegisterObserver(IObserverInterface* Observer)
{
	observers.Remove(Observer);
}
