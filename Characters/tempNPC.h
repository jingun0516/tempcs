#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "tempNPC.generated.h"

class ShopWidget;
class AHero;

UCLASS()
class CODESTORY_API AtempNPC : public ACharacter
{
	GENERATED_BODY()

public:
	AtempNPC();

protected:
	virtual void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	TSubclassOf<UShopWidget> shopClass;
	UShopWidget* shopWidget;
};
