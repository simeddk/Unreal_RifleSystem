#include "Weapons/CWeapon_AK47.h"
#include "Global.h"
#include "CMagazine.h"
#include "CWeaponComponent.h"
#include "Characters/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Widgets/CUserWidget_CrossHair.h"

ACWeapon_AK47::ACWeapon_AK47()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'");
	Mesh->SetSkeletalMesh(mesh);

	
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Dotsight, "DotSight", Mesh, "Dotsight");

	UStaticMesh* staticMesh;
	CHelpers::GetAsset<UStaticMesh>(&staticMesh, "StaticMesh'/Game/Weapons/Meshes/Accessories/SM_T4_Sight.SM_T4_Sight'");
	Dotsight->SetStaticMesh(staticMesh);
	Dotsight->SetRelativeScale3D(FVector(1, 0.95f, 1));


	BaseData.TargetArmLength = 200;
	BaseData.SocketOffset = FVector(0, 50, 15);
	BaseData.FieldOfView = 90;

	AimData.TargetArmLength = 30;
	AimData.SocketOffset = FVector(-55, 0, 10);
	AimData.FieldOfView = 55;


	LeftHandLocation = FVector(-35, 15.5f, 4);

	MagazineBoneName = "b_gun_mag";
	MagazineAttachSocketName = "Rifle_Magazine";
	EjectBoneName = "b_gun_shelleject";
	MuzzleBoneName = "Muzzle";


	CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Guns/BP_CameraShake_AK47.BP_CameraShake_AK47_C'");
	CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Guns/BP_CMagazine_AK47.BP_CMagazine_AK47_C'");

	CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Rifle_Reload_AK47_Montage.Rifle_Reload_AK47_Montage'");

	CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Rifle_Equip_AK47_Montage.Rifle_Equip_AK47_Montage'");
	HolsterSocketName = "Rifle_AK47_Holster";
	RightHandSocketName = "Rifle_AK47_RightHand";


	ArmsMeshTransform.SetLocation(FVector(-14.25f, -5.88f, -156.9f));
	ArmsMeshTransform.SetRotation(FQuat(FRotator(-0.5f, -11.85f, -1.2f)));

	ArmsLeftHandTransform.SetLocation(FVector(-33, 11, -1.5f));
	ArmsLeftHandTransform.SetRotation(FQuat(FRotator(-4, -138, 77)));
}

void ACWeapon_AK47::Begin_Equip()
{
	if (LeftHandSocketName.IsValid())
		AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), LeftHandSocketName);

	Owner->GetArms()->SetRelativeTransform(ArmsMeshTransform);
}

void ACWeapon_AK47::End_Equip()
{
	Super::End_Equip();

	if (RightHandSocketName.IsValid())
		AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), RightHandSocketName);
}

void ACWeapon_AK47::Begin_Aim()
{
	Super::Begin_Aim();

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Hidden);

	Owner->GetArms()->SetVisibility(true);
	Owner->GetMesh()->SetVisibility(false);
	Owner->GetBackpack()->SetVisibility(false);

	AttachToComponent(Owner->GetArms(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_Begin.Broadcast(this);
}

void ACWeapon_AK47::End_Aim()
{
	Super::End_Aim();

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Visible);

	Owner->GetArms()->SetVisibility(false);
	Owner->GetMesh()->SetVisibility(true);
	Owner->GetBackpack()->SetVisibility(true);

	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_End.Broadcast();
}