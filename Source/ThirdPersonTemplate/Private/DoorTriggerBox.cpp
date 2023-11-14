// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "TPSPlayer1.h"
#include "Kismet/GameplayStatics.h"
#include "DoorTriggerBox.h"

// Sets default values
ADoorTriggerBox::ADoorTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComp"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp -> SetupAttachment(boxComp);

	Niagara_ = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	Niagara_ -> SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ADoorTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	//boxComp = GetComponentByClass<UBoxComponent>();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorTriggerBox::OnPortalOverlapLevelLoadBegin);
}

// Called every frame

void ADoorTriggerBox::OnPortalOverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATPSPlayer1* _TPSPlayer = Cast<ATPSPlayer1>(OtherActor);

	//if (bForStream)
	{
	}//
	if (_TPSPlayer != nullptr && levelToLoad != "")
	{
		//UE_LOG(LogTemp, Warning, TEXT("TPSPlayer"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("TPSPlayer"));
		//////�����ε� 
		//UGameplayStatics::OpenLevel(this, levelToLoad);

		FLatentActionInfo LactentInfo;
		//�ε� ���� ��� ������ �������� ������ �ִ� ����ü
		UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, LactentInfo);
		//UGameplayStatics::UnLoadStreamLevel(this, levelToLoad, true, LactentInfo,true);
		//�ε���ü�� �������� �����ؾ�..
		LevelStreming(bLoad);
	}
	/*else if(bForAttractorControl)
	{
		AttractorControl();
	}*/
}

void ADoorTriggerBox::LevelStreming(bool stream)	
{
	FLatentActionInfo LactentInfo;

	//////�����ε� 
	////UGameplayStatics::OpenLevel(this, levelToLoad);

	//FLatentActionInfo LactentInfo;
	//�ε� ���� ��� ������ �������� ������ �ִ� ����ü
	//UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, LactentInfo);
	//UGameplayStatics::UnLoadStreamLevel(this, levelToLoad, true, LactentInfo,true);
	//�ε���ü�� �������� �����ؾ�..

	if (stream)
	{
		UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, LactentInfo);
	}
	else
	{
		UGameplayStatics::UnloadStreamLevel(this, levelToLoad, LactentInfo,true);
	}
}

void ADoorTriggerBox::AttractorControl()
{
	//if(AttachToActor)
}

void ADoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
