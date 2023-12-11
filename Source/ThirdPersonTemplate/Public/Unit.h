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
	//�Լ��� �������� ����
	//BlueprintNativeEvent : �������Ʈ���� ȣ���ϰų�  (�������̵� �ؼ�) �Լ������� �Ҽ��ֵ��� �����  ��ũ�� . �� c++ ,�������Ʈ ���� ��� ����������
	virtual void Attack_Implementation() PURE_VIRTUAL(AUnit::Attack_Implementation);
	//PURE_VIRTUAL : ���� ���� �Լ����� ��Ÿ���� ��ũ��
	//���������Լ��� �����̾��� , �Ļ�Ŭ�������� �ݵ�� �������̵��ؼ� ������ �ؾ���.
	// ���� AUnit Ŭ������ ����ϴ� Ŭ������ Attack_Implementation()�� �ݵ�� �����ؾ���.
	
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
