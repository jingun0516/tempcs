#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/CapsuleComponent.h>
#include "NPC.generated.h"

class UShopWidget;
class UTexture;
class UWidgetComponent;
class AHero;

UCLASS()
class CODESTORY_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPC();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	USkeletalMeshComponent* mesh = nullptr;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UCapsuleComponent* col = nullptr;

};
