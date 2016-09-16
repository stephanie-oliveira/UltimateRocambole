// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyBTTask_MoveToPlayer.h"
#include "Rocambole.h"
#include "MyBTService_CheckForPlayer.h"
#include "MyAIRocantroller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Robson.h"

	EBTNodeResult::Type UMyBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

	AMyAIRocantroller *PC = Cast <AMyAIRocantroller>(OwnerComp.GetAIOwner());

	ARobson* Player = Cast <ARobson>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(PC->EnemyKeyID));

	if (Player != nullptr) {

		PC->MoveToActor(Player, 20.0f, true, true, true, 0, true);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}





