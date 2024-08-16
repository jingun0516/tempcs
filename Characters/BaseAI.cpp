#include "BaseAI.h"
#include "AI/EnemyAIController.h"

ABaseAI::ABaseAI()
{
	SetCharacterMovement();
	AIControllerClass = AEnemyAIController::StaticClass();
}

void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

	//AEnemyAIController* AIController = GetWorld()->SpawnActor<AEnemyAIController>();
	//if (AIController)
	//{
	//	AIController->UnPossess();
	//	AIController->Possess(this);
	//}
}

void ABaseAI::SetCharacterMovement()
{
	Super::SetCharacterMovement();
}
