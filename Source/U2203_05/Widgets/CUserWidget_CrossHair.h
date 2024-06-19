#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_CrossHair.generated.h"

UCLASS()
class U2203_05_API UCUserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateSpreadRange(float InRadius, float InMaxRadius);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	TArray<class UBorder *> Borders;
	TArray<FVector2D> DefaultAlignments;

private:
	enum class EDirection
	{
		Top = 0, Bottom, Left, Right, Max,
	};

private:
	float Radius;
	float MaxRadius;
};
