// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSPlayer1.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyShowFx.generated.h"

/**
 * 
 * 
 */

//UAnimNotify 은 한프레임에만 실행하는 void Notify() 함수가 있고 , 
//UAnimNotifyState 은 3가지 경우로 나눠서 실행할수있도록 하는 함수가 있다(NotifyBegin, NotifyTick, NotifyEnd)
UCLASS()
class THIRDPERSONTEMPLATE_API UAnimNotifyShowFx : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	ATPSPlayer1* tpsPlayer;
};