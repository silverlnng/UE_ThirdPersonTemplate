#include "TPSPlayer1.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //바인딩 하는 함수 SetupPlayerInputComponent
#include "GameFramework/PlayerController.h"	//암기하기.  제어권의 컨트롤러 의미


// Sets default values
ATPSPlayer1::ATPSPlayer1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh (TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/unitychan.unitychan'"));	  //경로에 있는 데이터 로드
	//마지막 파일명을 바뀌면 문제가 됨

	if (initMesh.Succeeded()) // 그래서 방어코드 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object); //데이터 할당

		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true; //springArm은PawnControl을 따라가겠다 = Pawn을 축처럼 회전하게됨 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(springArmComp);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;  //pwan에 이미 할당되어있는 컴포넌트여서 바로 접근할수있음 
	
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
			//UInputMappingContext* PlayerMappingContext 를 에디터에서 할당하고 AddMappingContext으로 사용 ! 
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

		//여기서 바인딩을 해서 인풋때마다 Move , Fire 함수가 실행되는 것 
		// ETriggerEvent::Started,Completed ,,등 을 조절해서 바인드 액션을 조절할수있다


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
		//CurrentValue 의 x,y 는 input 값으로 공간벡터의 x,y 가 아님 

		//moveDir.x y 는 공간벡터. 그래서 CurrentValue와 별개 .
		moveDir.X = CurrentValue.Y;
		moveDir.Y = CurrentValue.X;
	}

}

void ATPSPlayer1::LookUp(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerPitchInput(_currentValue);	 //pwan에 이미 할당되어있는 컴포넌트여서 바로 접근할수있음 
}

void ATPSPlayer1::Turn(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerYawInput(_currentValue);	 //pwan에 이미 할당되어있는 컴포넌트여서 바로 접근할수있음 
}

void ATPSPlayer1::JumpInput(const FInputActionValue& Value)
{
	Jump();
}

void ATPSPlayer1::Locomotion()
{
	//이동방향을 컨트롤 방향 기준으로 변환

	//GetControlRotation()->FRotator -> FTransform 으로 감싸서 FTransform으로 변화 

	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);

	AddMovementInput(moveDir);

	//방향을 초기화
	moveDir = FVector::ZeroVector;

}

