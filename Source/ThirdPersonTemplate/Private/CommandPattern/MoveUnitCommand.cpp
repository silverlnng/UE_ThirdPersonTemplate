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
	//이동전 위치를 기억하여 나중에 되돌릴 수있도록 만들기
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
