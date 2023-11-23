// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyShowFx.h"
#include "TPSPlayer1.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyShowFx::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	tpsPlayer = Cast<ATPSPlayer1>(MeshComp->GetOwner());
	if (tpsPlayer)
	{
		//bool show = tpsPlayer->GetCharacterMovement()->IsFalling();
		tpsPlayer->ShowFx();
	}
}
