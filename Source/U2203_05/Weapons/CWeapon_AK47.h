#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_AK47.generated.h"

UCLASS()
class U2203_05_API ACWeapon_AK47 : public ACWeapon
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName LeftHandSocketName = "Rifle_AK47_LeftHand";

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Dotsight;

public:
	ACWeapon_AK47();

public:
	void Begin_Equip() override;
	void End_Equip() override;

	void Begin_Aim() override;
	void End_Aim() override;
};
