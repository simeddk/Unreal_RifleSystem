#include "CAnimNotifyState_Reload.h"
#include "Global.h"
#include "Characters/CPlayer.h"
//#include "Weapons/CRifle.h"

FString UCAnimNotifyState_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotifyState_Reload::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	//player->GetRifle()->Begin_Reload();
}

void UCAnimNotifyState_Reload::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	//player->GetRifle()->End_Reload();
}