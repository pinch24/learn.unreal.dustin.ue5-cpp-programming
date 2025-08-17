#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/ABCharacterBase.h"
#include "Interface/ABCharacterHUDInterface.h"
#include "ABCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase, public IABCharacterHUDInterface
{
	GENERATED_BODY()

public:
	// Constructor
	AABCharacterPlayer();
	
protected:
    virtual void BeginPlay() override;
	virtual void SetDead() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Owner() override;
	virtual void PostNetInit() override;

	// Character Control Section
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData) override;

	// Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CAMERA, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	void ShoulderLook(const FInputActionValue& Value);
	void ShoulderMove(const FInputActionValue& Value);
	
	void QuaterMove(const FInputActionValue& Value);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void Attack();
	virtual void AttackHitCheck() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttack();

	UPROPERTY(ReplicatedUsing = OnRep_CanAttack)
	uint8 bCanAttack: 1;

	UFUNCTION()
	void OnRep_CanAttack();

	float AttackTime = 1.4667f;

	ECharacterControlType CurrentCharacterControlType;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UI Section
	virtual void SetupHUDWidget(class UABHUDWidget* InHUDWidget) override;
};
