#include "MainInventoryWidget.h"
#include "InventorySlotsWidget.h"

void UMainInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

FReply UMainInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    FKey KeyPressed = InKeyEvent.GetKey();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (KeyPressed == EKeys::I)
    {
		UE_LOG(LogTemp, Log, TEXT("Keyboard Event I"));

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
