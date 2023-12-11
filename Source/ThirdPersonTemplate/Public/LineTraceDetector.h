// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTraceDetector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONTEMPLATE_API ULineTraceDetector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULineTraceDetector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void performLineTrace();
	
private:
	UPROPERTY(EditAnywhere)
	float traceDistance = 1000.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorClassToTrace;

	UFUNCTION()
	void OnLineTraceHit(FHitResult hitResult);
	
};
