#include "Weapons/item1.h"

Aitem1::Aitem1()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> textureFinder(TEXT("/Game/Items/item1"));
	if (textureFinder.Succeeded())
		itemImage = textureFinder.Object;
}
