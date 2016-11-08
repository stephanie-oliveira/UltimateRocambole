// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyBTService_CheckForPlayer.h"
#include "MyAIRocantroller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Robson.h"

void UMyBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	AMyAIRocantroller *PC = Cast<AMyAIRocantroller>(OwnerComp.GetAIOwner());

	if (PC != nullptr) {

		ARobson* Player = Cast <ARobson>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Player != nullptr) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(PC->EnemyKeyID, Player);

			
		}
	}
}

