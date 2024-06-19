#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Reload.generated.h"

UENUM()
enum class EMagazineActionType : uint8
{
	Eject, Spawn, Load, End,
};

UCLASS()
class U2203_05_API UCAnimNotify_Reload : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Magazine")
		EMagazineActionType ActionType;

public:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
