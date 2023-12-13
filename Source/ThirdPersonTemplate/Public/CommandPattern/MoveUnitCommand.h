// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CommandPattern/Command.h"
#include "Unit.h"
#include "CoreMinimal.h"

/**
 * 
 */
class THIRDPERSONTEMPLATE_API MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(AUnit* unit,float X ,float Y);
	~MoveUnitCommand();
public:	
	virtual void Execute() override;
	virtual void Undo() override;

private:
	class AUnit* _unit;
	float _beforeX , _beforeY;
	float _X , _Y;
	
};
