// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "NiagaraComponent.h"
#include "TPSPlayer1.generated.h"



//Ŭ���� �߰� _ ���漱��
//�ĺ��ڸ� �����ϱ��� �ĺ����� ���縦 �����Ϸ��� �̸� �˸��� �� 

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

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite , Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Fire")
	class UStaticMeshComponent* weaponMeshComp;
	/*UPROPERTY(VisibleAnyWhere, Category = "Fire")
	class UArrowComponent* firePosition;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	// �����ϰ� ������ Input Mapping Context ��  �����Ϳ��� �Ҵ�  "Category = Input"

	UPROPERTY(EditAnywhere, Category = "particle")
	class UNiagaraComponent* Niagara_SkeletalMesh;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveIA;		//UInputAction ����� ����߰� , Ŭ���� ���漱�� �Ѵ� �ϱ� 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractionIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractionIA_N;

public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void JumpInput(const FInputActionValue& Value);
	void InteractionPositive(const FInputActionValue& Value);
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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Status")
	float maxHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Status")
	float currentHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Status")
	float maxMP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Status")
	float currentMP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float interactionDistance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Status")
	int64 money = 9999;
	
	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int64 inputVal);
};
