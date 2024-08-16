#include "Weapons/BaseItem.h"

ABaseItem::ABaseItem()
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

