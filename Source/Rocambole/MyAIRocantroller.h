// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MyAIRocantroller.generated.h"

/**
 * 
 */
UCLASS()
class ROCAMBOLE_API AMyAIRocantroller : public AAIController
{
	GENERATED_BODY()

public:

	AMyAIRocantroller();
	virtual void Possess(APawn* Pawn) override;
	uint8 EnemyKeyID;

private:

	UBlackboardComponent* BlackboardComp;
	UBehaviorTreeComponent* BehaviorComp;
	
	
	
};
