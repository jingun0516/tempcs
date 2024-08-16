#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class CODESTORY_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void BeginPlay() override;

public:	
	FORCEINLINE UTexture2D* GetItemImage() { return itemImage; }
	
protected:
	UTexture2D* itemImage;
};
