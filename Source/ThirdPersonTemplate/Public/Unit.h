// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Unit")
	void Attack();
	//함수를 구현하지 않음
	//BlueprintNativeEvent : 블루프린트에서 호출하거나  (오버라이드 해서) 함수구현도 할수있도록 만드는  매크로 . 즉 c++ ,블루프린트 구현 모두 가질수있음
	virtual void Attack_Implementation() PURE_VIRTUAL(AUnit::Attack_Implementation);
	//PURE_VIRTUAL : 순수 가상 함수임을 나타내는 매크로
	//순수가상함수는 구현이없고 , 파생클래스에서 반드시 오버라이드해서 구현을 해야함.
	// 따라서 AUnit 클래스를 상속하는 클래스는 Attack_Implementation()를 반드시 구현해야함.
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Unit")
	void Defend();
	virtual void Defend_Implementation() PURE_VIRTUAL(AUnit::Defend_Implementation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
