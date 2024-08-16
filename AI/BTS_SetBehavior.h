#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetBehavior.generated.h"

UENUM(BlueprintType)
enum class EBehaviorKeys : uint8
{
	E_Patrol UMETA(Displayname = "Patrol"),
	E_Track UMETA(Displayname = "Track")
};

UCLASS(Blueprintable)
class CODESTORY_API UBTS_SetBehavior : public UBTService
{
	GENERATED_BODY()

private:
	UBTS_SetBehavior();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SetBehavior(EBehaviorKeys behavior);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBoardKey", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector BehaviorKey;

	UBlackboardComponent* BlackBoardComp;
};
