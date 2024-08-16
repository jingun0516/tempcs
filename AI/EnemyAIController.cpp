#include "EnemyAIController.h"
#include "Characters/Hero.h"
#include "Characters/BaseCharacter.h"
#include "Characters/BaseAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTfinder(L"/Game/AI/BT_Enemy");
	if (BTfinder.Succeeded())
		BTAsset = BTfinder.Object;

	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
	blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComp");
	TargetLoc = FVector(0, 0, 0);
	//Perception√ ±‚»≠
	SetPerceptionSystem();

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	bFound = false;
	for (auto actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Log, TEXT("%s Perception Detected"), *actor->GetName());
		if (AHero* hero = Cast<AHero>(actor))
		{
			get_blackboard()->SetValueAsObject(TEXT("PlayerKey"), hero);
			AHero* herokey = Cast<AHero>(get_blackboard()->GetValueAsObject(TEXT("PlayerKey")));
			if (herokey)
				UE_LOG(LogTemp, Log, TEXT("Enemy Set Player PlayerKey Succeed : %s"), *herokey->GetName());
			bFound = true;
			break;
		}
	}
}

void AEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

