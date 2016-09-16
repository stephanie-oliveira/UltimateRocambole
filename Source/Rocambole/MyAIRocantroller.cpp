// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyAIRocantroller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIRocambole.h"

AMyAIRocantroller::AMyAIRocantroller() {

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));


}

void AMyAIRocantroller::Possess(APawn* Pawn) {

	Super::Possess(Pawn);

	AAIRocambole* Roca = Cast <AAIRocambole>(Pawn);

	if (Roca != nullptr && Roca->Behavior != nullptr) {

		BlackboardComp->InitializeBlackboard(
			*Roca->Behavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp-> StartTree(*Roca->Behavior);

	}
}




