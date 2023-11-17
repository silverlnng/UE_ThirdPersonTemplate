// Fill out your copyright notice in the Description page of Project Settings.


#include "PGrenade.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
APGrenade::APGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxCollionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(boxCollionComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(boxCollionComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));

	movementComp->InitialSpeed = Grenadespeed;
	movementComp->MaxSpeed = Grenadespeed;
}

// Called when the game starts or when spawned
void APGrenade::BeginPlay()
{
	Super::BeginPlay();
	boxCollionComp->OnComponentBeginOverlap.AddDynamic(this,&APGrenade::OnGrenadeOverlap);
	//충돌할때 델리게이트 설정 
}

// Called every frame
void APGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APGrenade::OnGrenadeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSeep, const FHitResult& SweepResult)
{
	
		UE_LOG(LogTemp, Log, TEXT("Overlap GetName :: %s"), *OtherActor->GetName());
		movementComp->StopMovementImmediately();
		movementComp->ProjectileGravityScale = 0.f;
		AttachToActor(OtherActor, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		//sphereCollionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

