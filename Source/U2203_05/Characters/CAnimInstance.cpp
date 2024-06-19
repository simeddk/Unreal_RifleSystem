#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(Owner);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	if (!!Weapon)
		Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

	SetPlayerState();
	SetWeaponState();
}

void UCAnimInstance::SetPlayerState()
{
	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	AimPitch = Owner->GetAimPitch();
}

void UCAnimInstance::SetWeaponState()
{
	bInAim = Weapon->IsInAim();
	bFiring = Weapon->IsFiring();
	LeftHandLocation = Weapon->GetLeftHandLocation();

	bUseIK = WeaponType != EWeaponType::Max;
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}