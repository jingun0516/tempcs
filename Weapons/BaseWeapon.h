#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class CODESTORY_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh = nullptr;

};
