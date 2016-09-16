// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "AIRocambole.h"


// Sets default values
AAIRocambole::AAIRocambole()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(GetCapsuleComponent());

}

// Called when the game starts or when spawned
void AAIRocambole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIRocambole::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAIRocambole::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

