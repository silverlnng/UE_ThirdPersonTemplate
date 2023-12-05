// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

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
	//RotateDirectionalLightWithTime(Sun);
	//GetTimeByTotalSec(DeltaTime);
	UpdateSunColorByHourMinute(Sun);
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

			UDirectionalLightComponent* DirectionalLightCom = directionalLight->GetComponent();

			FLinearColor interpolatedColor;
			float lightTime = currentHour + (currentMinute/60);
			if(lightTime>0 && lightTime <=3)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color24,Color3,lightTime/3.0f);
			}
			if(lightTime>3 && lightTime <=6)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color3,Color6,lightTime/3.0f);
			}
			if(lightTime>6 && lightTime <=9)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color6,Color9,lightTime/3.0f);
			}
			if(lightTime>9 && lightTime <=12)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color9,Color12,lightTime/3.0f);
			}
			if(lightTime>12 && lightTime <=15)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color12,Color15,lightTime/3.0f);
			}
			if(lightTime>15 && lightTime <=18)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color15,Color18,lightTime/3.0f);
			}
			if(lightTime>18 && lightTime <=21)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color18,Color21,lightTime/3.0f);
			}
			if(lightTime>21 && lightTime <=24)
			{
				interpolatedColor = FLinearColor::LerpUsingHSV(Color21,Color24,lightTime/3.0f);
			}
			DirectionalLightCom->SetLightColor(interpolatedColor);
		}
	}
}

void AClock::UpdateSunColorByHourMinute(AActor* owningActor)
{
	UDirectionalLightComponent* directionalLight = Cast<ADirectionalLight>(owningActor)->GetComponent();
	float lightTime = currentHour + (currentMinute/60);

	//시간값을 24시간 단위로 설정
	lightTime = FMath::Fmod(lightTime,24.f);
	

	currentColorIndex = (FMath::FloorToInt(lightTime/3.f)) % (sunColors.Num());

	//sunColors.Num()==8
	//lightTime 0~3 ==>0  % 8 = 0
	//lightTime 3~6 ==>1  % 8 = 1
	//lightTime 6~9 ==>2  % 8 = 2

	//lightTime 21~24 ==>7 % 8 = 7
	
	float interpolationVector = (lightTime-(currentColorIndex*3)) / 3.f;
	//보간을 적용하는 비율
	//lightTime은 점점 증가
	
	if(currentColorIndex+1<sunColors.Num())
	{
		FLinearColor interpolatedColor = FLinearColor::LerpUsingHSV(sunColors[currentColorIndex],
		sunColors[currentColorIndex+1],interpolationVector);

		directionalLight->SetLightColor(interpolatedColor);
	}
	else //lightTime 21~24 ==>7 % 8 = 7인 경우
	{
		FLinearColor interpolatedColor = FLinearColor::LerpUsingHSV(sunColors[currentColorIndex],
		sunColors[0],interpolationVector);
		
		directionalLight->SetLightColor(interpolatedColor);
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
