#include "InventoryComponent.h"
#include "Weapons/BaseItem.h"

UInventoryComponent::UInventoryComponent()
{
}

void UInventoryComponent::SetItem(int index, ABaseItem* inItem)
{
	itemInven[index] = inItem;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

