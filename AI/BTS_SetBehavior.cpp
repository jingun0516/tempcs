#include "AI/BTS_SetBehavior.h"
#include "AI/BaseAIController.h"
#include "Characters/BaseAI.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"



UBTS_SetBehavior::UBTS_SetBehavior()
{
	NodeName = TEXT("SetBehaviorService");
}

void UBTS_SetBehavior::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto AICharacter = Cast<ABaseAI>(Controller->GetPawn());

	BlackBoardComp = OwnerComp.GetBlackboardComponent();

	ABaseCharacter* enemy = Cast<ABaseCharacter>(BlackBoardComp->GetValueAsObject(TEXT("PlayerKey")));
	
	if (enemy)
	{
		SetBehavior(EBehaviorKeys::E_Track);
		UE_LOG(LogTemp, Log, TEXT("Track"));
	}
	else
	{
		SetBehavior(EBehaviorKeys::E_Patrol);
		UE_LOG(LogTemp, Log, TEXT("Patrol"));
	}
}

void UBTS_SetBehavior::SetBehavior(EBehaviorKeys behavior)
{
	if (!BlackBoardComp) return;

	BlackBoardComp->SetValueAsEnum(BehaviorKey.SelectedKeyName, static_cast<uint8>(behavior));
}
