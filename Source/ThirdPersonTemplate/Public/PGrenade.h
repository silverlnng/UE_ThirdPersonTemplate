// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGrenade.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API APGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleAnywhere , Category = "Movement")
	class UProjectileMovementComponent* movementComp;	//포물선운동을 하는 기능

	UPROPERTY(EditAnywhere , Category = "collision")
	class UBoxComponent* boxCollionComp;

	UPROPERTY(EditAnywhere , Category = "mesh")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere , Category = "mesh")
	float Grenadespeed;

	void OnGrenadeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult);
	
};
