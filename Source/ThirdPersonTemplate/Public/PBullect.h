// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PBullect.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API APBullect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APBullect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere , Category = "Movement")
	class UProjectileMovementComponent* movementComp;	//포물선운동을 하는 기능

	UPROPERTY(VisibleAnywhere , Category = "collision")
	class USphereComponent* sphereCollionComp;

	UPROPERTY(VisibleAnywhere , Category = "mesh")
	class UStaticMeshComponent* meshComp;

	void Die();
};
