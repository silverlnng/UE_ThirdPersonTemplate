// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DoorTriggerBox.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API ADoorTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "particle")
	class UNiagaraComponent* Niagara_;

	UFUNCTION()
	void OnPortalOverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = "Level")
	FName levelToLoad;
	UPROPERTY(EditAnywhere, Category = "MainFunction")
	bool bForStream;
	UPROPERTY(EditAnywhere, Category = "MainFunction")
	bool bLoad;
	UPROPERTY(EditAnywhere, Category = "MainFunction")
	bool bForAttractorControl;

	UPROPERTY(EditAnywhere, Category = "AttractorControl")
	bool bForAttractorControl;


	void LevelStreming(bool stream);
	void AttractorControl();
};
