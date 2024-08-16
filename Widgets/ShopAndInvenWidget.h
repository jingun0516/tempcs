#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopAndInvenWidget.generated.h"

class UMainInventoryWidget;
class UShopWidget;
/**
 * 
 */
UCLASS()
class CODESTORY_API UShopAndInvenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItem(int index, ABaseItem* item);

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMainInventoryWidget* WB_MainInventory;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UShopWidget* WB_Shop;
};
