#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_Pistol.generated.h"

UCLASS()
class U2203_05_API ACWeapon_Pistol : public ACWeapon
{
	GENERATED_BODY()

public:
	ACWeapon_Pistol();

protected:
	virtual void BeginPlay() override;

public:
	void Begin_Equip() override;

	void Begin_Aim() override;
	void End_Aim() override;
};
