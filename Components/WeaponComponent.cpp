#include "WeaponComponent.h"
#include "../Weapons/BaseWeapon.h"
#include "../Characters/Hero.h"

UWeaponComponent::UWeaponComponent()
{
	ConstructorHelpers::FClassFinder<ABaseWeapon> weaponFinder1(TEXT("/Game/Weapons/BP_Weapon1"));
	ConstructorHelpers::FClassFinder<ABaseWeapon> weaponFinder2(TEXT("/Game/Weapons/BP_Weapon2"));
	if (weaponFinder1.Succeeded())
		WeaponClass1 = weaponFinder1.Class;
	if (weaponFinder2.Succeeded())
		WeaponClass2 = weaponFinder2.Class;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerHero = Cast<AHero>(GetOwner());
	if (!OwnerHero) return;

	OwnerHero->DFirstWeaponSelect.AddUFunction(this, "SelectFirstWeapon");
	OwnerHero->DSecondWeaponSelect.AddUFunction(this, "SelectSecondWeapon");
	
	if (!WeaponClass1 || !WeaponClass2) return;
	Weapon1 = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass1);
	Weapon2 = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass2);
	if (!Weapon1 || !Weapon2) return;

	SelectFirstWeapon();
}

void UWeaponComponent::SelectFirstWeapon()
{
	UE_LOG(LogTemp, Log, TEXT("first"));
	if (CurrentWeapon == Weapon1) return;
	Weapon1->AttachToComponent
	(
		OwnerHero->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		L"HandleSocket"
	);
	Weapon2->AttachToComponent
	(
		OwnerHero->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		L"HolsterSocket"
	);
	CurrentWeapon = Weapon1;
}

void UWeaponComponent::SelectSecondWeapon()
{
	UE_LOG(LogTemp, Log, TEXT("second"));
	if (CurrentWeapon == Weapon2) return;

	Weapon2->AttachToComponent
	(
		OwnerHero->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		L"HandleSocket"
	);
	Weapon1->AttachToComponent
	(
		OwnerHero->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		L"HolsterSocket"
	);

	CurrentWeapon = Weapon2;
}

