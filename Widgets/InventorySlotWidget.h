#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "InventorySlotWidget.generated.h"

class UDragDropOperation;
class AHero;
class ABaseItem;
/**
 *
 */
UCLASS()
class CODESTORY_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	void SetInvenImage(UTexture2D* texture);

	UFUNCTION(BlueprintCallable)
	void SetIndex(int InIndex) { index = InIndex; }

	FORCEINLINE int GetIndex() { return index; }

	void SetItem(ABaseItem* inItem);
	FORCEINLINE void BrushInvenImage(UTexture2D* texture) { InvenImage->SetBrushFromTexture(texture); }
	FORCEINLINE FSlateBrush GetInvenImageBrush() { return InvenImage->GetBrush(); }
	FORCEINLINE void ImageBrush(FSlateBrush brush) { InvenImage->SetBrush(brush); }

private:
	UPROPERTY(meta = (BindWidget))
	UImage* InvenImage;

	int index;
	bool bIsDragging;
	FVector2D DragStartPosition;
	FVector2D DragEndPosition;
	UInventorySlotWidget* tempWidget;
	FSlateBrush baseImage;
	AHero* OwnerHero;
	ABaseItem* item;
};
