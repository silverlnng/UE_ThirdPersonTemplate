// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
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

	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	// �����ϰ� ������ Input Mapping Context ��  �����Ϳ��� �Ҵ�  "Category = Input"

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveIA;		//UInputAction ����� ����߰� , Ŭ���� ���漱�� �Ѵ� �ϱ� 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpIA;


public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void JumpInput(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere,Category = "Move")
	float moveSpeed;

private:
	FVector moveDir;

	void Locomotion();
};
