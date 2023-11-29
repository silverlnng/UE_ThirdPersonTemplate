#include "TPSPlayer1.h"
#include "PBullect.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //바인딩 하는 함수 SetupPlayerInputComponent
#include "GameFramework/PlayerController.h"	//암기하기.  제어권의 컨트롤러 의미
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include  "DrawDebugHelpers.h"




// Sets default values
ATPSPlayer1::ATPSPlayer1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Resource/unitychan.unitychan'"));	  //경로에 있는 데이터 로드
	//마지막 파일명을 바뀌면 문제가 됨

	if (initMesh.Succeeded()) // 그래서 방어코드 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object); //GetMesh()가 캐릭터의 Skeletalmesh를 리턴 .그리고 데이터 할당

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

	//에셋을 넣기 위해서는 일단은 에셋 mesh을 넣을 그릇 staticMeshComponent 를 생성하기 

	weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshCompo"));
	weaponMeshComp->SetupAttachment(GetMesh(),FName(TEXT("RightHandSocket")));		
	//GetMesh()가 캐릭터의 Skeletalmesh를 리턴
	//FName 은 검색속도가 최적화 (단 영어한정)

	//ConstructorHelpers::FObjectFinder<UStaticMesh> staffMesh (TEXT("/Script/Engine.StaticMesh'/Game/Resource/Sraff///WizardStaff_Staff.WizardStaff_Staff'"));
	//
	//if (staffMesh.Succeeded()) // 그래서 방어코드 
	//{
	//	weaponMeshComp->SetStaticMesh(staffMesh.Object);
	//}

	fireCoolTime = 1.85f;
	fireTimerTime = 0;
	fireReady = true;

	maxHP=100;
	currentHP=0;
	maxMP=100;
	currentMP=0;
	
	interactionDistance = 2000.f;
	
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
	weaponMeshComp->SetupAttachment(GetMesh(), FName(TEXT("RightHandSocket")));
	

	Niagara_SkeletalMesh = GetComponentByClass<UNiagaraComponent>();
	if (Niagara_SkeletalMesh)
	{
		Niagara_SkeletalMesh->SetVisibility(false);
	}

}

// Called every frame
void ATPSPlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Locomotion();
	if (!fireReady)
	{
		fireCoolTimer(fireCoolTime, DeltaTime);
	}
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
		//EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Completed, this, &ATPSPlayer1::JumpInput);
		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Triggered, this, &ATPSPlayer1::Fire);
		EnhancedInputComponent->BindAction(InteractionIA, ETriggerEvent::Started, this, &ATPSPlayer1::InteractionPositive);
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
	//점프시작할때만 is falling을 체크 
	/*if (Value.Get<bool>() == true)
	{
		ShowFx(true);
	}*/
	/*else
	{
		ShowFx(false);
	}*/
}

void ATPSPlayer1::InteractionPositive(const FInputActionValue& Value)
{
	FVector _location;
	FRotator _rotation;
	FHitResult _hitOut;
	GetController()->GetPlayerViewPoint(_location,_rotation);
	//플레이어의 뷰포인트 == 카메라가 보고있는 뷰 != 캐릭터의 시점아님 
	//플레이어의 뷰포인트 ==> 캐릭터의 시점아님
	/*FVector _start = _location;
	FVector _End = (_rotation.Vector()*2000);*/

	FVector _start = GetActorLocation();
	FVector _End = GetActorLocation() +(GetActorForwardVector() * interactionDistance); // 2000-> Disatance
	
	FCollisionQueryParams _traceParams;		//
	GetWorld()->LineTraceSingleByChannel(_hitOut,_start,_End,ECC_Visibility,_traceParams);
	DrawDebugLine(GetWorld(),_start,_End,FColor::Cyan,false,2.0f);
}


void ATPSPlayer1::Locomotion()
{
	//이동방향을 컨트롤 방향 기준으로 변환

	//GetControlRotation()->FRotator -> FTransform 으로 감싸서 FTransform으로 변화 

	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);

	AddMovementInput(moveDir);		//

	//방향을 초기화
	moveDir = FVector::ZeroVector;

}

void ATPSPlayer1::fireCoolTimer(float Duration , float deltaTime)
{
	if (fireTimerTime <Duration)
	{
		fireTimerTime += deltaTime;
		fireReady = false;
	}
	else
	{
		fireTimerTime = 0;
		fireReady = true;
	}
}

void ATPSPlayer1::SpawnBullect()
{
	FTransform Socket_firePosition = weaponMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<APBullect>(bullectFactory, Socket_firePosition);
}

void ATPSPlayer1::Fire(const FInputActionValue& Value)
{
	//FTransform Socket_firePosition = weaponMeshComp->GetSocketTransform(TEXT("FirePosition"));
	//weaponMeshComp 의 메쉬자체를 클릭해서 socket생성한후 이름으로 소켓 검색 
	//FTransform 에 location , rotation , scale 다들어가있음 ! 

	if (Controller && Value.Get<bool>() == true)
	{
		//GetWorld()->SpawnActor<APBullect>(bullectFactory, Socket_firePosition);
		//FTransform 에 크기도 들어가서 소켓의 크기에 비례해서 생성됨 
		//weaponMeshComp크기가 0.3 이고 weaponMeshComp의 소켓의 상대적크기 relativeScale 3.0 
		//생성되는 총알 크기는 0.9 로 나옴 
		

		UAnimInstance* animInstance = GetMesh() -> GetAnimInstance();
		//animclass의 복사본에 접근하기 위해서 . AnimInstance을 사용 
		if (fireReady)
		{
			if (animInstance)
			{
				animInstance->Montage_Play(fireAnimMotage);
			}

			fireReady = false;
		}
	}
	
}

void ATPSPlayer1::ShowFx()
{
	if (Niagara_SkeletalMesh == nullptr)	//null값일때만 다시 get하도록하는 방어코드
	{
		Niagara_SkeletalMesh = GetComponentByClass<UNiagaraComponent>();
	}
	bool show = GetCharacterMovement()->IsFalling();
	Niagara_SkeletalMesh->SetVisibility(show);
}

void ATPSPlayer1::UpdateMoney(int64 inputVal)
{
	int64 _result;
	_result = money + inputVal;
	if (_result < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("NotEnoughMoney"));
	}
	else
	{
		money = _result;
	}
}
