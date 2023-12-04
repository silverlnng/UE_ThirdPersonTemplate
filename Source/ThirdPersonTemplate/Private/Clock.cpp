// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include "Engine/DirectionalLight.h"

#define ONE_YEAR 31104000
#define ONE_DAY 
#define ONE_HOUR 
#define ONE_MINUTE
// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);
	RotateDirectionalLightWithTime(Sun);
	//GetTimeByTotalSec(DeltaTime);
}


void AClock::UpdateTime(float DeltaSec)
{
	TotalSecond +=DeltaSec*tiemScale;

	currentDay = TotalSecond/86400;
	int RemainingAfterDay = (int)TotalSecond%86400;

	currentHour = RemainingAfterDay/3600;
	int RemaingAfterHour = RemainingAfterDay%3600;

	currentMinute = RemaingAfterHour/60;
	currentSecond = RemaingAfterHour%60;
}

void AClock::RotateDirectionalLightWithTime(AActor* owningActor)
{
	if(owningActor)
	{
		ADirectionalLight* directionalLight = Cast<ADirectionalLight>(owningActor);
		if(directionalLight)
		{
			//float anglePerHour = 360.0f/24.0f; //360도를 24 시간으로 나눔 =15
			//float hourAngle = FMath::Fmod(currentHour*anglePerHour,360.0f);
			float hourAngle = FMath::Fmod(currentHour*15,360.0f);	//시간에 따른 각도계산
			float minuteAngle = (currentMinute/60.0f)*15;
			float secondAngle = (currentMinute/60.0f)*(15/60.0f);
			float currentAngle =hourAngle +minuteAngle+secondAngle;
			FRotator newRotation = FRotator(currentAngle,0.0f,0.0f);
			directionalLight->SetActorRotation(newRotation);
			
		}
	}
}

FString AClock::GetTimeByTotalSec(float totalSec)
{
	//YEAR = totalSec/ONE_YEAR;
	//urrentDay =(int)totalSec/ONE_DAY % 30;
	//currentHour = (int)totalSec/ONE_HOUR % 24;

	FString Now;
	Now = "D:" + FString::SanitizeFloat(currentDay);
	
	return FString();
}
