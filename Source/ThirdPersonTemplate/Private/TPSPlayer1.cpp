#include "TPSPlayer1.h"
#include "PBullect.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //���ε� �ϴ� �Լ� SetupPlayerInputComponent
#include "GameFramework/PlayerController.h"	//�ϱ��ϱ�.  ������� ��Ʈ�ѷ� �ǹ�
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"




// Sets default values
ATPSPlayer1::ATPSPlayer1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/unitychan.unitychan'"));	  //��ο� �ִ� ������ �ε�
	//������ ���ϸ��� �ٲ�� ������ ��

	if (initMesh.Succeeded()) // �׷��� ����ڵ� 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object); //GetMesh()�� ĳ������ Skeletalmesh�� ���� .�׸��� ������ �Ҵ�

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

	//������ �ֱ� ���ؼ��� �ϴ��� ���� mesh�� ���� �׸� staticMeshComponent �� �����ϱ� 

	weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshCompo"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> staffMesh (TEXT("/Script/Engine.StaticMesh'/Game/Resource/Sraff/WizardStaff_Staff.WizardStaff_Staff'"));

	if (staffMesh.Succeeded()) // �׷��� ����ڵ� 
	{
		weaponMeshComp->SetStaticMesh(staffMesh.Object);
	}
	
	weaponMeshComp->SetupAttachment(GetMesh(),FName("RightHandSocket"));		//GetMesh()�� ĳ������ Skeletalmesh�� ����

	/*firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCompo"));
	firePosition->SetupAttachment(weaponMeshComp);*/
	fired = false;
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

	//auto lamdaFunc = []() -> void {
	//	UE_LOG(LogTemp, Warning, TEXT("lamda test"))

	//	};	//��������ó�� ���� ������������ ��밡�� 

	//lamdaFunc();

	/*int32 sum = 10;
	auto lamdaFunc_add = [&sum](int number)->void
		{
			sum += number;
		};
	lamdaFunc_add(20);
	UE_LOG(LogTemp, Warning, TEXT("sum: %d"), sum);

	TArray<int32> Numbers = { 1,2,3,4,5,6,7,8,9,10 };
	TArray<int32> EvenNumbers;
	
	for (const int32 i : Numbers)
	{
		if (i%2==0)
		{
			EvenNumbers.Add(i);
		}
	}

	auto lamda_print = [](int num) -> void
		{
			UE_LOG(LogTemp, Warning, TEXT("EvenNumbers : %d"), num);
		};

	for (const int32 i : EvenNumbers)
	{
		lamda_print(i);
	}*/

	//int a = 10;
	//int b = 5;
	//char operation = '+';

	//auto lamda_Caculator = [](int x, int y, char _operation)-> int 
	//{
	//		switch(_operation)
	//		{
	//		case '+':
	//			return x + y;
	//			break;
	//		case '-':
	//			return x - y;
	//			break;
	//		case '/':
	//			//�������� ���������� ���� ������ ���� 0 �� �ƴҶ��� ����
	//			if (y != 0)
	//			{
	//				return x / y;
	//			}
	//			else
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("Error : division by zero"));
	//				return 0;
	//			}
	//			break;
	//		default:
	//			UE_LOG(LogTemp, Warning, TEXT("Error : invalid operator"));
	//			return 0;
	//		};
	//};
	//int answer = lamda_Caculator(a, b, operation);
	//UE_LOG(LogTemp, Warning, TEXT("answer : %d"), answer);

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
		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::Fire);
		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Completed, this, &ATPSPlayer1::Fire);

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

	AddMovementInput(moveDir);		//

	//������ �ʱ�ȭ
	moveDir = FVector::ZeroVector;

}

void ATPSPlayer1::Fire(const FInputActionValue& Value)
{
	FTransform Socket_firePosition = weaponMeshComp->GetSocketTransform(TEXT("FirePosition"));
	//weaponMeshComp �� �޽���ü�� Ŭ���ؼ� socket�������� �̸����� ���� �˻� 
	//FTransform �� location , rotation , scale �ٵ����� ! 

	if (Controller && Value.Get<bool>() == true)
	{
		GetWorld()->SpawnActor<APBullect>(bullectFactory, Socket_firePosition);
		//FTransform �� ũ�⵵ ���� ������ ũ�⿡ ����ؼ� ������ 
		//weaponMeshCompũ�Ⱑ 0.3 �̰� weaponMeshComp�� ������ �����ũ�� relativeScale 3.0 
		//�����Ǵ� �Ѿ� ũ��� 0.9 �� ���� 

		UAnimInstance* animInstance = GetMesh() -> GetAnimInstance();
		//animclass�� ���纻�� �����ϱ� ���ؼ� . AnimInstance�� ��� 

		if (animInstance)
		{
			animInstance->Montage_Play(fireAnimMotage);
		}
		fired = true;
	}
	else
	{
		fired = false;
	}
}
