#include "Weapons/CWeapon_AR4.h"
#include "Global.h"
#include "CMagazine.h"
#include "Characters/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"

ACWeapon_AR4::ACWeapon_AR4()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	BaseData.TargetArmLength = 200;
	BaseData.SocketOffset = FVector(0, 50, 15);
	BaseData.FieldOfView = 90;

	AimData.TargetArmLength = 80;
	AimData.SocketOffset = FVector(0, 55, 10);
	AimData.FieldOfView = 65;

	
	LeftHandLocation = FVector(-30.0f, 15.5f, 7.0f);

	MagazineBoneName = "b_gun_mag";
	MagazineAttachSocketName = "Rifle_Magazine";
	EjectBoneName = "b_gun_shelleject";
	MuzzleBoneName = "Muzzle";


	CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Guns/BP_CameraShake_AR4.BP_CameraShake_AR4_C'");
	CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Guns/BP_CMagazine_AR4.BP_CMagazine_AR4_C'");

	CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Rifle_Reload_AR4_Montage.Rifle_Reload_AR4_Montage'");
	
	CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Rifle_Equip_AR4_Montage.Rifle_Equip_AR4_Montage'");
	HolsterSocketName = "Rifle_AR4_Holster";
	RightHandSocketName = "Rifle_AR4_RightHand";
}