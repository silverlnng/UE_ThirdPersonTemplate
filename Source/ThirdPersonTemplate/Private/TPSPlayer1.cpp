#include "TPSPlayer1.h"

#include <filesystem>
#include <SceneExport.h>

#include "CollisionDebugDrawingPublic.h"
#include "PBullect.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" //���ε� �ϴ� �Լ� SetupPlayerInputComponent
#include "GameFramework/PlayerController.h"	//�ϱ��ϱ�.  ������� ��Ʈ�ѷ� �ǹ�
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "PGrenade.h"
#include "Engine/World.h"
#include  "SlashHUD.h"
#include  "SlashOverlay.h"
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
	weaponMeshComp->SetupAttachment(GetMesh(),FName(TEXT("RightHandSocket")));		
	//GetMesh()�� ĳ������ Skeletalmesh�� ����
	//FName �� �˻��ӵ��� ����ȭ (�� ��������)

	//ConstructorHelpers::FObjectFinder<UStaticMesh> staffMesh (TEXT("/Script/Engine.StaticMesh'/Game/Resource/Sraff///WizardStaff_Staff.WizardStaff_Staff'"));
	//
	//if (staffMesh.Succeeded()) // �׷��� ����ڵ� 
	//{
	//	weaponMeshComp->SetStaticMesh(staffMesh.Object);
	//}

	fireCoolTime = 1.85f;
	fireTimerTime = 0;
	fireReady = true;

	originArrowSpwanLocation = weaponMeshComp->GetSocketTransform(FName("FirePosition_2")).GetLocation();
	
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
	weaponMeshComp->SetupAttachment(GetMesh(), FName(TEXT("RightHandSocket")));
	

	Niagara_SkeletalMesh = GetComponentByClass<UNiagaraComponent>();
	if (Niagara_SkeletalMesh)
	{
		Niagara_SkeletalMesh->SetVisibility(false);
	}

	//grenadeClass = APGrenade::StaticClass();
	//grenade_=Cast<APGrenade>(grenadeClass);
	//grenade_ = GetWorld()->SpawnActor(APGrenade::StaticClass());
	//grenade_ =Cast<APGrenade>(GetWorld()->SpawnActor(APGrenade::StaticClass()));
	// ó������ �������� 0�� ���·�  �����Ǵٰ� �ð��� ������ �ƿ� ������°� Ȯ�ε�.

	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		ASlashHUD* slashHUD =Cast<ASlashHUD>(playerController->GetHUD());
		if(slashHUD)
		{
			USlashOverlay*  SlashOverlay = slashHUD->GetSlashOverlay();
			if(SlashOverlay)
			{
				SlashOverlay->SetGoldText("goldText");
			}
		}
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

	TraceForArrow();
	ProjectilePath();
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
		EnhancedInputComponent->BindAction(Fkeyboard_IA, ETriggerEvent::Triggered, this, &ATPSPlayer1::Fkeyboard);
		
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
	//���������Ҷ��� is falling�� üũ 
	/*if (Value.Get<bool>() == true)
	{
		ShowFx(true);
	}*/
	/*else
	{
		ShowFx(false);
	}*/
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
	//GetWorld()->SpawnActor<APBullect>(bullectFactory, Socket_firePosition);
	//FTransform �� ũ�⵵ ���� ������ ũ�⿡ ����ؼ� ������ 
	//weaponMeshCompũ�Ⱑ 0.3 �̰� weaponMeshComp�� ������ �����ũ�� relativeScale 3.0 
	//�����Ǵ� �Ѿ� ũ��� 0.9 �� ���� 
}

void ATPSPlayer1::Fire(const FInputActionValue& Value)
{
	//FTransform Socket_firePosition = weaponMeshComp->GetSocketTransform(TEXT("FirePosition"));
	//weaponMeshComp �� �޽���ü�� Ŭ���ؼ� socket�������� �̸����� ���� �˻� 
	//FTransform �� location , rotation , scale �ٵ����� ! 
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	//animclass�� ���纻�� �����ϱ� ���ؼ� . AnimInstance�� ��� 
	if (fireReady)
	{
		if (animInstance)
		{
			animInstance->Montage_Play(fireAnimMotage);
		}

		fireReady = false;
	}
}

void ATPSPlayer1::ShowFx()
{
	if (Niagara_SkeletalMesh == nullptr)	//null���϶��� �ٽ� get�ϵ����ϴ� ����ڵ�
	{
		Niagara_SkeletalMesh = GetComponentByClass<UNiagaraComponent>();
	}
	bool show = GetCharacterMovement()->IsFalling();
	Niagara_SkeletalMesh->SetVisibility(show);
}

void ATPSPlayer1::SpwanGrenade()
{
	//FTransform Socket_firePosition2 = weaponMeshComp->GetSocketTransform(TEXT("FirePosition_2"));
	FTransform Socket_firePosition2;
	Socket_firePosition2.SetLocation(weaponMeshComp->GetSocketLocation(TEXT("FirePosition_2")));
	Socket_firePosition2.SetRotation(TargetArrowSpwanRotation.Quaternion());
	GetWorld()->SpawnActor<APGrenade>(GrenadeFactory, Socket_firePosition2);
}

void ATPSPlayer1::TraceForArrow()
{
	// 1. ī�޶� �Ŵ����� �̿��ؼ� line trace�� ������ ���� ����
	APlayerCameraManager* PlayerCameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	FVector impactPoint;
	FVector CrossHairWorldLocation;
	CrossHairWorldLocation = PlayerCameraManager->GetActorTransform().GetLocation();
	impactPoint = (PlayerCameraManager->GetActorForwardVector())*15000.f+CrossHairWorldLocation;
	
	// 2. ����Ʈ���̽� �׸��� hit , hit�� �ƴѰ�� ������ 
	FHitResult HitResult;
	FCollisionQueryParams param;
	TArray<FHitResult> Hits;
	TArray<AActor*> actorToIgnore;
	actorToIgnore.Add(this);
	
	//ActorLineTraceSingle(HitResult,CrossHairWorldLocation,impactPoint,ECC_Visibility,param);
	//bool hitResult_bool = ActorLineTraceSingle(HitResult,CrossHairWorldLocation,impactPoint,ECC_Visibility,param);
	//ActorLineTraceSingle(CrossHairWorldLocation,impactPoint)
	
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),CrossHairWorldLocation,impactPoint,ETraceTypeQuery::TraceTypeQuery1,false,actorToIgnore,
	EDrawDebugTrace::ForOneFrame,HitResult, true,FLinearColor::Red, FLinearColor::Green,5.f);
	
	//DrawLineTraces(GetWorld(),CrossHairWorldLocation,impactPoint,Hits,5.0f);
	
	//UE_LOG(LogTemp, Log, TEXT("hitResult_bool :: %s"), HitResult.IsValidBlockingHit() ? TEXT("true") : TEXT("false"));

	originArrowSpwanLocation = weaponMeshComp->GetSocketTransform(FName("FirePosition_2")).GetLocation();
	//��ġ�� tick ���� ��� �������ֵ��� �����
	
	
	if(HitResult.IsValidBlockingHit())
	{
		impactPoint = HitResult.Location;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("hitResult_bool"));
	}
	TargetArrowSpwanRotation = UKismetMathLibrary::MakeRotFromX(impactPoint -originArrowSpwanLocation);
	// 3.  	
	
}

void ATPSPlayer1::ClearArc()
{
}

void ATPSPlayer1::ProjectilePath()
{
	FPredictProjectilePathParams PredictProjectilePathParam
	(   10.f,
		originArrowSpwanLocation,
		UKismetMathLibrary::GetForwardVector(TargetArrowSpwanRotation)*(grenadeSpeed),
		10.0f
	);
	PredictProjectilePathParam.DrawDebugType=EDrawDebugTrace::Type::ForOneFrame;
	//FPredictProjectilePathParams ����ü
	
	FPredictProjectilePathResult PredictResult;
	
	UGameplayStatics::PredictProjectilePath(GetWorld(),PredictProjectilePathParam,PredictResult);
}

void ATPSPlayer1::ChangeWeapon()
{
	//Ű������ ���� ������ <-> ����ź �����ؼ� �����Ҽ��ֵ��� �ϱ�

	//Ű������ ui ���� ���� 
	

	
}

void ATPSPlayer1::Fkeyboard(const FInputActionValue& Value)
{
	if (fireReady)
	{
		SpwanGrenade();
		fireReady = false;
	}
}
