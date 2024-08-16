#include "tempNPC.h"
#include "../Widgets/ShopWidget.h"
#include "Hero.h"

AtempNPC::AtempNPC()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn"));
	if (mesh.Succeeded())
		GetMesh()->SetSkeletalMesh(mesh.Object);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UShopWidget> shop(TEXT("/Game/Widgets/WB_Shop"));
	if (shop.Succeeded())
		shopClass = shop.Class;
}

void AtempNPC::BeginPlay()
{
	Super::BeginPlay();
	
	if (shopClass)
	{
		shopWidget = CreateWidget<UShopWidget>(GetWorld(), shopClass);
		if (!shopWidget) return;
		shopWidget->AddToViewport();
		shopWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AtempNPC::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(Cast<AHero>(OtherActor))
		shopWidget->SetVisibility(ESlateVisibility::Visible);
}

void AtempNPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AHero>(OtherActor))
		shopWidget->SetVisibility(ESlateVisibility::Hidden);
}
