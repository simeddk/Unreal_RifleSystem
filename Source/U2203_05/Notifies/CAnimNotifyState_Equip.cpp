#include "Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Weapons/CWeaponComponent.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);
	CheckNull(weapon);

	weapon->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);
	CheckNull(weapon);

	weapon->End_Equip();
}
