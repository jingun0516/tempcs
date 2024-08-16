#include "ShopWidget.h"
#include "InventorySlotsWidget.h"
#include "InventorySlotWidget.h"
#include "../Weapons/BaseItem.h"

void UShopWidget::SetItem(int index, ABaseItem* item)
{
	TMap<int, UInventorySlotWidget*> invenSlot = GetInventorySlotsWidget()->GetInventorySlot();
	invenSlot[index]->BrushInvenImage(item->GetItemImage());
	invenSlot[index]->SetItem(item);
}

void UShopWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Log, TEXT("Mouse Entered!!"));
	SetFocus();
}
