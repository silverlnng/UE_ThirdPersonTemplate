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
	// 인터페이스에서 일반함수처럼 선언해서 
	// 함수명 + _Implementation : 함수지정자로 인터페이스에서 override를 할 함수를 찾아야됨 

	virtual void play() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
