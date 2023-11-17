// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyStateFire.h"
#include "TPSPlayer1.h"


void UNotifyStateFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Notify�� �ҷ����� ���� ù(1) ������
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("NotifyBegin"));
	//GEngine->AddOnScreenDebugMessage() : �������Ʈ���� printString

	tpsPlayer = Cast<ATPSPlayer1>(MeshComp->GetOwner());
	// ���⼭ MeshComp�� �ִϸ��̼��� �÷����ϴ� SkeletalMeshComponent�� �Ű������� ���´� 
	// ���������������� , �÷��̿����� ���������� cast�Ǿ� �۵��Ѵ�. tpsPlayer�� ���������� ���̵��� nullüũ�� ���� �ʰ� tpsPlayer->SpawnBullect(); �� �ص� �����۵�.
	// preview ȯ�濡���� tpsPlayer ã���� ���Ѵ� .�׷��� cast �Ѵ��� tpsPlayer�� null���̴�.

	if (tpsPlayer)      // �׷��� null üũ ���ֱ� 
	{
		tpsPlayer->SpawnBullect();
		tpsPlayer->SpwanGrenade();
	}
}

void UNotifyStateFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Magenta, TEXT("NotifyTick"));
	//Notify�� �ҷ����� ������ �� ������
}

void UNotifyStateFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Blue, TEXT("NotifyEnd"));
	//Notify�� ������ (1) ������
	
}
