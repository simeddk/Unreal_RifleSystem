#include "CAnimNotify_Reload.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Weapons/CWeaponComponent.h"

FString UCAnimNotify_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);
	CheckNull(weapon);

	switch (ActionType)
	{
		case EMagazineActionType::Eject: weapon->Eject_Magazine(); break;
		case EMagazineActionType::Spawn: weapon->Spawn_Magazine(); break;
		case EMagazineActionType::Load: weapon->Load_Magazine(); break;
		case EMagazineActionType::End: weapon->End_Reload(); break;
	}
}