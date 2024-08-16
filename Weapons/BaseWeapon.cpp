#include "BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorEnableCollision(true);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
