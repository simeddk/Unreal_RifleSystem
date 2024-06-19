#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CPlayer.generated.h"

UCLASS()
class U2203_05_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Backpack;

public:
	FORCEINLINE class USkeletalMeshComponent* GetArms() { return Arms; }
	FORCEINLINE class UStaticMeshComponent* GetBackpack() { return Backpack; }

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);

public:
	void UseControlRotation();
	void NotUseControlRotation();
};
