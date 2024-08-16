#include "BaseAIController.h"
#include "../Characters/BaseAI.h"
#include "Characters/Hero.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig_Sight.h" // ��: �ð� ���� ����
#include "Perception/AISenseConfig_Hearing.h" // ��: û�� ���� ����
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTAsset)
		RunBehaviorTree(BTAsset);
	if (BTComp)
		BTComp->StartTree(*BTAsset);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AICharacter = Cast<ABaseAI>(InPawn);
}
