// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class CODESTORY_API AEnemyAIController : public ABaseAIController
{
	GENERATED_BODY()

protected:
	AEnemyAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;
	bool bFound = false;
	FVector TargetLoc = FVector(0, 0, 0);
	FVector bbLoc = FVector(0, 0, 0);

public:
	FORCEINLINE void SetTargetLoc(FVector InLoc) { TargetLoc = InLoc; }
	FORCEINLINE FVector GetTargetLoc() { return TargetLoc; }
	FORCEINLINE FVector GetBBLoc() { return bbLoc; }

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void SetPerceptionSystem();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILoseSightRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AIFieldOfView = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILastSeenLocation = 900.f;
};
