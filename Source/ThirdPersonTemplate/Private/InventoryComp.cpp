// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComp.h"

// Sets default values for this component's properties
UInventoryComp::UInventoryComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComp::AddItem(const FName& ItemName, int32 Quantity)
{
	int32* existingQuantity = inventoryMap.Find(ItemName);
	if(existingQuantity)
	{
		*existingQuantity +=Quantity;
		//포인터가 가르키는 값을 수정해서 다시 add를 안해줘도 됨
	}
	else
	{
		inventoryMap.Add(ItemName,Quantity);
	}
	
	/*if(inventoryMap.Find(ItemName))
	{
		inventoryMap.Add(ItemName,*inventoryMap.Find(ItemName)+Quantity);
	}
	else
	{
		inventoryMap.Add(ItemName,Quantity);
	}*/
}

void UInventoryComp::RemoveItem(const FName& ItemName, int32 Quantity)
{
	int32* existingQuantity = inventoryMap.Find(ItemName);

	if(existingQuantity)
	{
		*existingQuantity-=Quantity;
		//포인터가 가르키는 값을 수정해서 다시 add를 안해줘도 됨
		if(*existingQuantity<=0)
		{
			inventoryMap.Remove(ItemName);
		}
	}
	/*if(inventoryMap.Find(ItemName))
	{
		if(*inventoryMap.Find(ItemName)-1>0)
		{
			inventoryMap.Add(ItemName,*inventoryMap.Find(ItemName)-1);
		}
		else
		{
			inventoryMap.Remove(ItemName);
		}
	}*/
	
}

int32 UInventoryComp::GetItemQuantity(const FName& ItemName) const
{
	const int32* existingQuantity = inventoryMap.Find(ItemName);
	//없을떄를 방어하기
	return existingQuantity? *existingQuantity : 0;
}


// Called when the game starts
void UInventoryComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

