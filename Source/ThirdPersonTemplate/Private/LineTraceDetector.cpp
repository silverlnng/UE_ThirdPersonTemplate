// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTraceDetector.h"
#include "Engine/World.h"
#include  "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULineTraceDetector::ULineTraceDetector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULineTraceDetector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULineTraceDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULineTraceDetector::performLineTrace()
{
	FVector start = GetOwner()->GetActorLocation();
	FVector end = start+GetOwner()->GetActorForwardVector()*traceDistance;
	FHitResult outHit;
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor((GetOwner()));	//자기자신을 제외시켜지도록 설정
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(outHit,start,end,ECC_Visibility,collisionQueryParams);
	DrawDebugLine(GetWorld(),start,end,FColor::Blue,false,3.0f);
	if(bHit)
	{
		OnLineTraceHit(outHit);
	}
	
}

void ULineTraceDetector::OnLineTraceHit(FHitResult hitResult)
{
	if(hitResult.GetActor() && hitResult.GetActor()->IsA(actorClassToTrace))
	{
		//원하는 클래스의 액터를 찾은 경우
		//프레임 차이 안에 삭제가 될수 있어서 valid 체크를 다시하기  
		AActor* foundActor = hitResult.GetActor();
		if(foundActor)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green, (TEXT("%s"), *foundActor->GetName()));
		}
		
	}
}

