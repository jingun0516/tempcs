#include "NPC.h"
#include "Hero.h"
#include "../Widgets/ShopWidget.h"
#include "../Widgets/InventorySlotsWidget.h"
#include "../Widgets/InventorySlotWidget.h"
#include "../Weapons/item1.h"
#include "../Weapons/item2.h"
#include <Components/WidgetComponent.h>

ANPC::ANPC()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh Component");
	col = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	col->SetupAttachment(mesh);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshFinder(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn"));
	if (meshFinder.Succeeded())
		mesh->SetSkeletalMesh(meshFinder.Object);
	mesh->SetSimulatePhysics(true);
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
}
