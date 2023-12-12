// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableActor.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();
	
	virtual void Interact_Implementation(AActor* otherActor) override;
	// �������̽����� �Ϲ��Լ�ó�� �����ؼ� 
	// �Լ��� + _Implementation : �Լ������ڷ� �������̽����� override�� �� �Լ��� ã�ƾߵ� 

	virtual void play() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
