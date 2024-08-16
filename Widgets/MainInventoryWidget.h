// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainInventoryWidget.generated.h"

class UInventorySlotsWidget;
/**
 *
 */
UCLASS()
class CODESTORY_API UMainInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventorySlotsWidget* GetInventorySlotsWidget() { return WB_InventorySlots; }
	virtual void NativeConstruct() override;

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UInventorySlotsWidget* WB_InventorySlots;
};
