// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WalkerL.generated.h"

UCLASS()
class ROCAMBOLE_API AWalkerL : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalkerL();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//get e set do Life
	void SetLife(int NewLife);
	int GetLife();


private:

	int Cont = 0;

	int ContBomb = 0;

	int Life = 20;


	bool Right = true;
	bool Down = false;
	bool Left = false;
	bool Up = false;
	bool Up2 = false;
	bool Right2 = false;



	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnyWhere, Category = Tick)
		float RunningTime;

	//UFUNCTION()
		//void OnHit(UPrimitiveComponent* HitComponen, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	
	void DropBomb();

	
	
};
