// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "NiagaraComponent.h"
#include "TPSPlayer1.generated.h"



//클래스 추가 _ 전방선언
//식별자를 정의하기전 식별자의 존재를 컴파일러에 미리 알리는 것 

class UInputMappingContext;
class UInputAction;

UCLASS()
class THIRDPERSONTEMPLATE_API ATPSPlayer1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
	class UStaticMeshComponent* weaponMeshComp;
	/*UPROPERTY(VisibleAnyWhere, Category = "Fire")
	class UArrowComponent* firePosition;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	// 선언하고 만들어둔 Input Mapping Context 를  에디터에서 할당  "Category = Input"

	UPROPERTY(EditAnywhere, Category = "particle")
	class UNiagaraComponent* Niagara_SkeletalMesh;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveIA;		//UInputAction 사용은 헤더추가 , 클래스 전방선언 둘다 하기 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Fkeyboard_IA;
	//F 버튼 누르면 무기 선택 ui 창 나오고 그후에 마우스 클릭으로 발사하도록 만들기
	

public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void JumpInput(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Fire(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere,Category = "Move")
	float moveSpeed;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class APBullect> bullectFactory;

	UPROPERTY(EditAnywhere, Category = "animation")
	UAnimMontage* fireAnimMotage;

private:
	void Locomotion();
	FVector moveDir;
public:
	UPROPERTY(EditAnywhere, Category = "Fire")
	bool fireReady;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float fireTimerTime;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float fireCoolTime;
protected:
	void fireCoolTimer(float Duration, float deltaTime);

public:
	void SpawnBullect();
	void ShowFx();

	// 화살 포물선 그리면서 날리기
	void SpwanGrenade();
	void TraceForArrow();
	FVector originArrowSpwanLocation;
	FRotator TargetArrowSpwanRotation;
	void ClearArc();
	void ProjectilePath();
	void ChangeWeapon();

	UPROPERTY(EditAnywhere, Category = "Grenade")
	TSubclassOf<class APGrenade> GrenadeFactory;
	
	UPROPERTY(EditAnywhere, Category = "Grenade")
	UClass* grenadeClass;
	UPROPERTY(EditAnywhere, Category = "Grenade")
	APGrenade* grenade_;
	
	UPROPERTY(EditAnywhere, Category = "Grenade")
	float grenadeSpeed;
	
	void Fkeyboard(const FInputActionValue& Value);
};
