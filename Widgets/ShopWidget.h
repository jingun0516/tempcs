// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UInventorySlotsWidget;
class ABaseItem;
/**
 * 
 */
UCLASS()
class CODESTORY_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventorySlotsWidget* GetInventorySlotsWidget() { return WB_InventorySlots; }
	void SetItem(int index, ABaseItem* item);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UInventorySlotsWidget* WB_InventorySlots;
};
