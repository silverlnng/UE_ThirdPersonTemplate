// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

AEnemy::AEnemy()
{
}

void AEnemy::Attack_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Enemy is attacking"));
}

void AEnemy::Defend_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Enemy is defending"));
}
