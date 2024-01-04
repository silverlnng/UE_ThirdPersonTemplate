// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
}

void AGoblin::Attack_Implementation()
{
	//����� ���ݱ�� ����
	UE_LOG(LogTemp,Warning,TEXT("Goblin is attacking"));

	//���ݴɷ��� ����ϸ� ���������� �˸��� �������Ѵ�
	// ������ ����� for������ ��� ��ȸ 
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
	// ��� ���� ��� ��� ���� 
	UE_LOG(LogTemp,Warning,TEXT("Goblin is defending"));
}

void AGoblin::NotifyAttack()
{
	
}

void AGoblin::RegisterObserver(IObserverInterface* Observer)
{
	// ������ ���
	observers.AddUnique(Observer);
}

void AGoblin::UnRegisterObserver(IObserverInterface* Observer)
{
	//������ ����
	observers.Remove(Observer);
}
