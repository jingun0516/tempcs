#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotsWidget.generated.h"

class UInventorySlotWidget;
/**
 *
 */
UCLASS()
class CODESTORY_API UInventorySlotsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE TMap<int, UInventorySlotWidget*> GetInventorySlot() { return InventorySlot; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UInventorySlotWidget*> InventorySlot;
};
