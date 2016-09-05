// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bomba.generated.h"

UCLASS()
class ROCAMBOLE_API ABomba : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomba();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	//cria como esfera
	UBoxComponent* Root;
	UStaticMeshComponent * MeshComp;


	//movimentação do projétil
	//UProjectileMovementComponent* ProjectileMovement;

	//float DefaultZ;

	
};
