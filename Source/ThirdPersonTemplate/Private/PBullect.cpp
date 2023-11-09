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
	SetRootComponent(sphereCollionComp);			//���� RootComponent = sphereCollionComp;	
	const float Radius = 13.0f;
	sphereCollionComp->SetSphereRadius(Radius);
	sphereCollionComp->SetCollisionProfileName(TEXT("BlockAll"));
	

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(sphereCollionComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);	//�޽����Ե� �ݸ����� ���� !! �� �ݸ����� �Ⱦ��ڴٰ� ����

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	//�߻�ü ������Ʈ�� ����
	//�߻�ü�� ������Ʈ�� ������Ʈ ��ų ������Ʈ�� ���� = ������Ʈ�� ��ų��� = ���� root component(�浹ü) �� �����ؼ� �������� �׵��� ��������� ����°�.
	//�ð����������� ������ ������Ʈ //�ð����������� ������ tick
	movementComp->SetUpdatedComponent(sphereCollionComp);
	
	movementComp->InitialSpeed = 3000.0f;			//�ʱ�ӵ�
	movementComp->MaxSpeed = 5000.0f;				//�ִ�ӵ�
	movementComp->bShouldBounce = true;				//�ݵ��� ����
	movementComp->Bounciness = 0.3f;				//�ݵ��� ũ�� ���� �������� �ݵ��� ���� 

	//InitialLifeSpan = 2.0f;		//actor�� �ִ� ������ 2���Ŀ� destroy

}

// Called when the game starts or when spawned
void APBullect::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle deathTimer;	//Ÿ�̸Ӹ� �����ϴ� ���� ~= �˶� , �𸮾��� ��� 
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &APBullect::Die, 2.0f, false);
	//(�˸�(FTimerHandle) , �˸�ó���� �� ��ü , �˸� ó�� �Լ� , �˸��ð� , �ݺ����� , ���ʵ����̽ð�)

	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void{Destroy();}), 4.0f, false);
	//���ٷ� ����ó�� 


}
// Called every frame
void APBullect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APBullect::Die()
{
	Destroy();
}

