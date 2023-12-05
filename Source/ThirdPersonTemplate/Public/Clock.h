// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float currentDay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float currentHour;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float currentMinute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float currentSecond;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float TotalSecond;
	UFUNCTION(BlueprintCallable)
	FString GetTimeByTotalSec(float totalSec);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	float tiemScale = 1;
	UPROPERTY(EditAnywhere, Category="sun")
	class AActor* Sun;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color6;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color9;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color12;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color15;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color18;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color21;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Time")
	FLinearColor Color24;

	UPROPERTY(EditAnywhere,Category="Sun")
	TArray<FLinearColor> sunColors;
	
protected:
	void UpdateTime(float DeltaSec);

	void RotateDirectionalLightWithTime(AActor* owningActor);

	void UpdateSunColorByHourMinute(AActor* owningActor);

	int currentColorIndex;
};
