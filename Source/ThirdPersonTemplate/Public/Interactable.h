// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 인터페이스는 순수가상함수들"만" 있음
 */
class THIRDPERSONTEMPLATE_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Interactable")
	void Interact(AActor* instigator);
	// UFUNCTION(BlueprintNativeEvent 을 사용하기 위해서 일반함수로 정의
	// 그래서 override를 할 쪽에서는 함수명+_Implementation 으로 override 를 함 
	// 인터페이스를 상속받는쪽에서 정의 + 블루프린트에서 정의 둘다 가능 

	virtual void play() = 0;
	// 순수가상함수로 지정했을 경우
	// virtual은 UFUNCTION(BlueprintNativeEvent) 지정을 못함
	// 인터페이스를 상속받는 쪽에서만 정의 가능 
};
