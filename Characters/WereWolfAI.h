// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "WereWolfAI.generated.h"

/**
 * 
 */
UCLASS()
class CODESTORY_API AWereWolfAI : public ABaseAI
{
	GENERATED_BODY()
	
public:
	AWereWolfAI();

protected:
	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
