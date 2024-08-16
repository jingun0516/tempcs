#include "InventorySlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragDrop.h"
#include "../Characters/Hero.h"
#include "../Weapons/BaseItem.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	baseImage = InvenImage->GetBrush();

	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Log, TEXT("LeftClick Detected Slot Index: %d"), index);
	//if (baseImage != InvenImage->GetBrush())
	{
		if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
		{
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			UE_LOG(LogTemp, Log, TEXT("Drag Detected"));
		}
	}
	return reply.NativeReply;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDrop* DragDrop = NewObject<UDragDrop>();

	DragDrop->WidgetReference = this;
	DragDrop->DropOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDrop->DefaultDragVisual = this;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->Payload = this;

	OutOperation = DragDrop;
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDrop* oper = Cast<UDragDrop>(InOperation);

	if (!oper) return false;

	if (UInventorySlotWidget* slot = Cast<UInventorySlotWidget>(oper->Payload))
	{
		FSlateBrush originBrush = InvenImage->GetBrush();			// 기존 브러시
		FSlateBrush dropBrush = slot->GetInvenImageBrush();			// 드랍될 브러시

		ImageBrush(dropBrush);
		slot->ImageBrush(originBrush);

	}
	return true;
}

void UInventorySlotWidget::SetInvenImage(UTexture2D* texture)
{
	InvenImage->SetBrushFromTexture(texture);
}

void UInventorySlotWidget::SetItem(ABaseItem* inItem)
{
	this->item = inItem;
	InvenImage->SetBrushFromTexture(inItem->GetItemImage());
}
