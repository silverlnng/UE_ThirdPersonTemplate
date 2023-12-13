// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandPattern/MoveUnitCommand.h"

MoveUnitCommand::MoveUnitCommand(AUnit* unit,float X ,float Y)
{
	_unit = unit;
	_beforeX=0;
	_beforeY=0;
	_X=X;
	_Y=Y;
}

MoveUnitCommand::~MoveUnitCommand()
{
}

void MoveUnitCommand::Execute()
{
	//�̵��� ��ġ�� ����Ͽ� ���߿� �ǵ��� ���ֵ��� �����
	_beforeX = _unit->GetActorLocation().X;
	_beforeY = _unit->GetActorLocation().Y;

	FVector newLoc = FVector(_X,_Y,_unit->GetActorLocation().Z);
	_unit->SetActorLocation(newLoc);
}

void MoveUnitCommand::Undo()
{
	FVector beforeLoc = FVector(_beforeX,_beforeY,_unit->GetActorLocation().Z);
	_unit->SetActorLocation(beforeLoc);
}
