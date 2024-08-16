// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NameWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class CODESTORY_API UNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetName(FText name);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;
};
