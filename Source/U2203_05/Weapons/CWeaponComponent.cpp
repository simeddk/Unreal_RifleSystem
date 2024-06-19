#include "Weapons/CWeaponComponent.h"
#include "Global.h"
#include "CWeapon.h"
#include "Widgets/CUserWidget_HUD.h"
#include "Characters/CPlayer.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetClass<UCUserWidget_HUD>(&HUDClass, "WidgetBlueprint'/Game/Widgets/WB_HUD.WB_HUD_C'");
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (TSubclassOf<ACWeapon> weaponClass : WeaponClasses)
	{
		if (!!weaponClass)
		{
			ACWeapon* weapon = Owner->GetWorld()->SpawnActor<ACWeapon>(weaponClass, params);
			Weapons.Add(weapon);
		}
	}

	if (!!HUDClass)
	{
		HUD = CreateWidget<UCUserWidget_HUD, APlayerController>(Owner->GetController<APlayerController>(), HUDClass);
		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Hidden);
	}

	OnWeaponAim_Arms_Begin.AddDynamic(this, &UCWeaponComponent::On_Begin_Aim);
	OnWeaponAim_Arms_End.AddDynamic(this, &UCWeaponComponent::On_End_Aim);
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetCurrWeapon())
	{
		if (!!HUD)
		{
			GetCurrWeapon()->IsAutoFire() ? HUD->OnAutoFire() : HUD->OffAutoFire();


			uint8 currMagazineCount = GetCurrWeapon()->GetCurrMagazineCount();
			uint8 maxMagazineCount = GetCurrWeapon()->GetMaxMagazineCount();

			HUD->UpdateMagazine(currMagazineCount, maxMagazineCount);

			HUD->UpdateWeaponName(Type);
		}

		return;
	}
}

ACWeapon* UCWeaponComponent::GetCurrWeapon()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);

	return Weapons[(int32)Type];
}

void UCWeaponComponent::SetUnarmedMode()
{
	CheckFalse(GetCurrWeapon()->CanUnequip());

	GetCurrWeapon()->Unequip();
	ChangeType(EWeaponType::Max);

	Owner->NotUseControlRotation();
	HUD->SetVisibility(ESlateVisibility::Hidden);
}

void UCWeaponComponent::SetAR4Mode()
{
	SetMode(EWeaponType::AR4);
}

void UCWeaponComponent::SetAK47Mode()
{
	SetMode(EWeaponType::AK47);
}

void UCWeaponComponent::SetPistolMode()
{
	SetMode(EWeaponType::Pistol);
}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{
		CheckFalse(GetCurrWeapon()->CanUnequip());

		GetCurrWeapon()->Unequip();
	}


	CheckNull(Weapons[(int32)InType]);
	CheckFalse(Weapons[(int32)InType]->CanEquip());

	Weapons[(int32)InType]->Equip();
	Owner->UseControlRotation();

	ChangeType(InType);
	HUD->SetVisibility(ESlateVisibility::Visible);
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;

	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevType, InType);
}

bool UCWeaponComponent::IsInAim()
{
	CheckNullResult(GetCurrWeapon(), false);

	return GetCurrWeapon()->IsInAim();
}

bool UCWeaponComponent::IsFiring()
{
	CheckNullResult(GetCurrWeapon(), false);

	return GetCurrWeapon()->IsFiring();
}

FVector UCWeaponComponent::GetLeftHandLocation()
{
	CheckNullResult(GetCurrWeapon(), FVector::ZeroVector);

	return GetCurrWeapon()->GetLeftHandLocation();
}

FTransform UCWeaponComponent::GetArmsLeftHandTransform()
{
	CheckNullResult(GetCurrWeapon(), FTransform());

	return GetCurrWeapon()->GetArmsLeftHandTransform();
}

void UCWeaponComponent::Begin_Equip()
{
	CheckNull(GetCurrWeapon());

	GetCurrWeapon()->Begin_Equip();
}

void UCWeaponComponent::End_Equip()
{
	CheckNull(GetCurrWeapon());

	GetCurrWeapon()->End_Equip();
}

void UCWeaponComponent::Begin_Aim()
{
	CheckNull(GetCurrWeapon());
	CheckFalse(GetCurrWeapon()->CanAim());

	GetCurrWeapon()->Begin_Aim();
}

void UCWeaponComponent::End_Aim()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->End_Aim();
}

void UCWeaponComponent::Begin_Fire()
{
	CheckNull(GetCurrWeapon());
	CheckFalse(GetCurrWeapon()->CanFire());

	GetCurrWeapon()->Begin_Fire();
}

void UCWeaponComponent::End_Fire()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->End_Fire();
}

void UCWeaponComponent::ToggleAutoFire()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->ToggleAutoFire();
}

void UCWeaponComponent::Reload()
{
	CheckNull(GetCurrWeapon());
	CheckFalse(GetCurrWeapon()->CanReload());

	GetCurrWeapon()->Reload();
}

void UCWeaponComponent::Eject_Magazine()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->Eject_Magazine();
}

void UCWeaponComponent::Spawn_Magazine()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->Spawn_Magazine();
}

void UCWeaponComponent::Load_Magazine()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->Load_Magazine();
}

void UCWeaponComponent::End_Reload()
{
	CheckNull(GetCurrWeapon());
	GetCurrWeapon()->End_Reload();
}

void UCWeaponComponent::On_Begin_Aim(ACWeapon* InThisObject)
{
	for (ACWeapon* weapon : Weapons)
	{
		if (weapon == InThisObject)
			continue;

		weapon->SetHidden(true);
	}
}

void UCWeaponComponent::On_End_Aim()
{
	for (ACWeapon* weapon : Weapons)
		weapon->SetHidden(false);
}