#include "Characters/CCharacter.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/CWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);


	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator prev = FRotator(AimPitch, AimYaw, 0);
	FRotator curr = UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(), GetActorRotation());

	FRotator delta = UKismetMathLibrary::RInterpTo(prev, curr, DeltaTime, ViewInterpSpeed);
	AimPitch = FMath::Clamp(delta.Pitch, PitchRange.X, PitchRange.Y);
	AimYaw = FMath::Clamp(delta.Yaw, YawRange.X, YawRange.Y);
}
