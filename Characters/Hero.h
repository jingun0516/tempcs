// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Hero.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UCameraComponent;
class UWidgetComponent;
class UNameWidget;
class USetNameWidget;
class UWeaponComponent;
class UMainInventoryWidget;
class UShopAndInvenWidget;
class UShopWidget;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE(FFirstWeaponSelect);					
DECLARE_MULTICAST_DELEGATE(FSecondWeaponSelect);
DECLARE_MULTICAST_DELEGATE(FOpenInven);
/**
 * 
 */
UCLASS()
class CODESTORY_API AHero : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHero();

	FORCEINLINE void SetNickName(FText InNickName) { NickName = InNickName; }
	void FinishSetNickName();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent
	(UInputComponent* PlayerInputComponent) override;

	virtual void SetCharacterMovement() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	void CreateCamera();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* FirstWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenInven;

public:
	void DoFirstSelect();
	void DoSecondSelect();
	void DoOpenInven();
	void DoOpenShopAndInven();
	FFirstWeaponSelect DFirstWeaponSelect;
	FSecondWeaponSelect DSecondWeaponSelect;
	FOpenInven DOpenInven;

	bool IsShopOpen() { return bShopOpen; }
	bool IsInvenOpen() { return bInvenOpen; }
	void SetShopOpen(bool shop) { bShopOpen = shop; }
	void SetInvenOpen(bool inven) { bInvenOpen = inven; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UWidgetComponent* NameWidgetComp;
	TSubclassOf<UNameWidget> NameClass;
	UNameWidget* NameWidget;

	TSubclassOf<USetNameWidget> SetNameClass;
	USetNameWidget* SetNameWidget;

	TSubclassOf<UShopAndInvenWidget> ShopAndInvenClass;
	UShopAndInvenWidget* ShopAndInvenWidget;

	TSubclassOf<UShopWidget> ShopClass;
	UShopWidget* ShopWidget;

	FText NickName;

	TSubclassOf<UMainInventoryWidget> InvenClass;
	UMainInventoryWidget* InvenWidget;

	bool bShopOpen = false;
	bool bInvenOpen = false;
};
