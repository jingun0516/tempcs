#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
class AHero;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODESTORY_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void SelectFirstWeapon();
	UFUNCTION()
	void SelectSecondWeapon();

	AHero* OwnerHero;
	TSubclassOf<ABaseWeapon> WeaponClass1;
	TSubclassOf<ABaseWeapon> WeaponClass2;
	ABaseWeapon* Weapon1;
	ABaseWeapon* Weapon2;
	
	ABaseWeapon* CurrentWeapon = nullptr;
};
