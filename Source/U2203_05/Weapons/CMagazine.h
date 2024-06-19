#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

UCLASS()
class U2203_05_API ACMagazine : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh_Empty;

public:	
	ACMagazine();

protected:
	virtual void BeginPlay() override;

public:
	void Eject();

private:
	bool bEject;
};
