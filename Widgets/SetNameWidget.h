// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/EditableTextBox.h>
#include "Components/Button.h"
#include "SetNameWidget.generated.h"

class UEditableTextBox;
class UButton;
class AHero;
/**
 * 
 */
UCLASS()
class CODESTORY_API USetNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetNickName(FText nickName);
	UFUNCTION()
	void OnNickNameButtonClicked();
	UFUNCTION()
	void OnNickNameChanged(const FText& Text);
private:
	virtual void NativeOnInitialized() override;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* NickNameText;

	UPROPERTY(meta = (BindWidget))
	UButton* NickNameButton;

	AHero* OwnerHero;
};
