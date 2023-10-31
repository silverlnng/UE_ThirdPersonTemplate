#include "TPSPlayer1.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPSPlayer1::ATPSPlayer1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh (TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/unitychan.unitychan'"));	  //��ο� �ִ°� �������� 

	if (initMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object);

		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));		//����
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;

}

// Called when the game starts or when spawned
void ATPSPlayer1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSPlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSPlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

