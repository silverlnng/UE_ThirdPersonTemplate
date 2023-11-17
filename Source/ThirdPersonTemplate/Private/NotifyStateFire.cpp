// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyStateFire.h"
#include "TPSPlayer1.h"


void UNotifyStateFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Notify가 불려지면 시작 첫(1) 프레임
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("NotifyBegin"));
	//GEngine->AddOnScreenDebugMessage() : 블루프린트에서 printString

	tpsPlayer = Cast<ATPSPlayer1>(MeshComp->GetOwner());
	// 여기서 MeshComp는 애니메이션을 플레이하는 SkeletalMeshComponent가 매개변수로 들어온다 
	// 문법적오류도없고 , 플레이에서는 정상적으로 cast되어 작동한다. tpsPlayer에 정상적으로 값이들어가서 null체크를 하지 않고도 tpsPlayer->SpawnBullect(); 를 해도 정상작동.
	// preview 환경에서는 tpsPlayer 찾지를 못한다 .그래서 cast 한다음 tpsPlayer은 null값이다.

	if (tpsPlayer)      // 그래서 null 체크 해주기 
	{
		tpsPlayer->SpawnBullect();
		tpsPlayer->SpwanGrenade();
	}
}

void UNotifyStateFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Magenta, TEXT("NotifyTick"));
	//Notify가 불려지는 동안의 매 프레임
}

void UNotifyStateFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Blue, TEXT("NotifyEnd"));
	//Notify가 끝나는 (1) 프레임
	
}
