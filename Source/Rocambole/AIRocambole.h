// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIRocambole.generated.h"

UCLASS()
class ROCAMBOLE_API AAIRocambole : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIRocambole();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* Behavior;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	
	
};
