// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class CODESTORY_API ABaseAI : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseAI();
	

protected:
	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
