// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONTEMPLATE_API UInventoryComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComp();

	UFUNCTION(BlueprintCallable)
	void AddItem(const FName& ItemName, int32 Quantity);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(const FName& ItemName, int32 Quantity);

	//해당아이템의 수량가져오기 
	UFUNCTION(BlueprintPure)
	int32 GetItemQuantity(const FName& ItemName) const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// TickComponent 인것에 주의
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TMap<FName,int32> inventoryMap;	//data는 private으로 이것에 대한 접근을 함수로 .
		
};
