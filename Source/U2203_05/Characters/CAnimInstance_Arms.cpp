#include "Characters/CAnimInstance_Arms.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/CPlayer.h"

void UCAnimInstance_Arms::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(Owner);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	if (!!Weapon)
		Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance_Arms::OnWeaponTypeChanged);
}

void UCAnimInstance_Arms::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	LeftHandTransform = Weapon->GetArmsLeftHandTransform();
}

void UCAnimInstance_Arms::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}