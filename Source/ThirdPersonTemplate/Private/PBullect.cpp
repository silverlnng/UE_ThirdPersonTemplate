// Fill out your copyright notice in the Description page of Project Settings.


#include "PBullect.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
APBullect::APBullect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereCollionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(sphereCollionComp);			//동일 RootComponent = sphereCollionComp;	
	const float Radius = 13.0f;
	sphereCollionComp->SetSphereRadius(Radius);
	sphereCollionComp->SetCollisionProfileName(TEXT("BlockAll"));
	

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(sphereCollionComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);	//메쉬에게도 콜리전이 있음 !! 그 콜리전을 안쓰겠다고 설정

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	//발사체 컴포넌트를 생성
	//발사체의 컨포넌트를 업데이트 시킬 컴포넌트를 지정 = 업데이트를 시킬대상 = 보통 root component(충돌체) 를 설정해서 나머지는 그도록 따라오도록 만드는것.
	//시간변수유무가 없으면 업데이트 //시간변수유무가 있으면 tick
	movementComp->SetUpdatedComponent(sphereCollionComp);
	
	movementComp->InitialSpeed = 3000.0f;			//초기속도
	movementComp->MaxSpeed = 5000.0f;				//최대속도
	movementComp->bShouldBounce = true;				//반동을 설정
	movementComp->Bounciness = 0.3f;				//반동의 크기 설정 작을수록 반동이 적음 

}

// Called when the game starts or when spawned
void APBullect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APBullect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

