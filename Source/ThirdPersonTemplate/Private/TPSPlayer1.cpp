#include "TPSPlayer1.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //���ε� �ϴ� �Լ� SetupPlayerInputComponent
#include "GameFramework/PlayerController.h"	//�ϱ��ϱ�.  ������� ��Ʈ�ѷ� �ǹ�


// Sets default values
ATPSPlayer1::ATPSPlayer1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh (TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/unitychan.unitychan'"));	  //��ο� �ִ� ������ �ε�
	//������ ���ϸ��� �ٲ�� ������ ��

	if (initMesh.Succeeded()) // �׷��� ����ڵ� 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object); //������ �Ҵ�

		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true; //springArm��PawnControl�� ���󰡰ڴ� = Pawn�� ��ó�� ȸ���ϰԵ� 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(springArmComp);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;  //pwan�� �̹� �Ҵ�Ǿ��ִ� ������Ʈ���� �ٷ� �����Ҽ����� 
	
	moveSpeed = 100.0f;

}

// Called when the game starts or when spawned
void ATPSPlayer1::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem <UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
			//UInputMappingContext* PlayerMappingContext �� �����Ϳ��� �Ҵ��ϰ� AddMappingContext���� ��� ! 
		}
	}

	
}

// Called every frame
void ATPSPlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Locomotion();
}

// Called to bind functionality to input
void ATPSPlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::JumpInput);

		//���⼭ ���ε��� �ؼ� ��ǲ������ Move , Fire �Լ��� ����Ǵ� �� 
		// ETriggerEvent::Started,Completed ,,�� �� �����ؼ� ���ε� �׼��� �����Ҽ��ִ�


	}
}

void ATPSPlayer1::Move(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();

	/*const float horizontal = CurrentValue.Y;
	const float vertical = CurrentValue.X;

	if (Controller)
	{
		AddMovementInput(GetActorRightVector(), vertical, true);
		AddMovementInput(GetActorForwardVector(), horizontal, true);
	}*/

	if (Controller)
	{
		//CurrentValue �� x,y �� input ������ ���������� x,y �� �ƴ� 

		//moveDir.x y �� ��������. �׷��� CurrentValue�� ���� .
		moveDir.X = CurrentValue.Y;
		moveDir.Y = CurrentValue.X;
	}

}

void ATPSPlayer1::LookUp(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerPitchInput(_currentValue);	 //pwan�� �̹� �Ҵ�Ǿ��ִ� ������Ʈ���� �ٷ� �����Ҽ����� 
}

void ATPSPlayer1::Turn(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerYawInput(_currentValue);	 //pwan�� �̹� �Ҵ�Ǿ��ִ� ������Ʈ���� �ٷ� �����Ҽ����� 
}

void ATPSPlayer1::JumpInput(const FInputActionValue& Value)
{
	Jump();
}

void ATPSPlayer1::Locomotion()
{
	//�̵������� ��Ʈ�� ���� �������� ��ȯ

	//GetControlRotation()->FRotator -> FTransform ���� ���μ� FTransform���� ��ȭ 

	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);

	AddMovementInput(moveDir);

	//������ �ʱ�ȭ
	moveDir = FVector::ZeroVector;

}

