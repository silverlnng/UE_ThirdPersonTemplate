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

//UAnimNotify �� �������ӿ��� �����ϴ� void Notify() �Լ��� �ְ� , 
//UAnimNotifyState �� 3���� ���� ������ �����Ҽ��ֵ��� �ϴ� �Լ��� �ִ�(NotifyBegin, NotifyTick, NotifyEnd)
UCLASS()
class THIRDPERSONTEMPLATE_API UAnimNotifyShowFx : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	ATPSPlayer1* tpsPlayer;
};