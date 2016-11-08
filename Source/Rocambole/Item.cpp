// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Item.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetCollisionProfileName("BlockAllDynamic");

	//simula f�sica
	//MeshComp->SetSimulatePhysics(true);
	//MeshComp->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int AItem::Use() {

	UE_LOG(LogTemp, Warning, TEXT("YOU FOUND A ROCAMBOLE!"));
	return 10;
}

