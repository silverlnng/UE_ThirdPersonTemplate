// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "TPSPlayer1.h"
#include "DoorTriggerBox.h"

// Sets default values
ADoorTriggerBox::ADoorTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	boxComp = GetComponentByClass<UBoxComponent>();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorTriggerBox::OnPortalOverlap);
}

// Called every frame
void ADoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorTriggerBox::OnPortalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATPSPlayer1* TPSPlayer = Cast<ATPSPlayer1>(OtherActor);

	if (TPSPlayer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("TPSPlayer"));
		//레벨로드 
	}
}

