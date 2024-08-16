#include "Weapons/item2.h"

Aitem2::Aitem2()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> textureFinder(TEXT("/Game/Items/item2"));
	if (textureFinder.Succeeded())
		itemImage = textureFinder.Object;
}
