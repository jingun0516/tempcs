#include "Widgets/ShopAndInvenWidget.h"
#include "Weapons/BaseItem.h"
#include "InventorySlotWidget.h"
#include "InventorySlotsWidget.h"
#include "MainInventoryWidget.h"
#include "ShopWidget.h"

void UShopAndInvenWidget::SetItem(int index, ABaseItem* item)
{
	TMap<int, UInventorySlotWidget*> invenSlot = WB_Shop->GetInventorySlotsWidget()->GetInventorySlot();
	invenSlot[index]->BrushInvenImage(item->GetItemImage());
	invenSlot[index]->SetItem(item);
}

FReply UShopAndInvenWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey KeyPressed = InKeyEvent.GetKey();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (KeyPressed == EKeys::I)
	{
		if (GetVisibility() == ESlateVisibility::Visible)
		{
			if (!PlayerController) return FReply::Handled();

			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);

			SetVisibility(ESlateVisibility::Hidden);
		}

		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
