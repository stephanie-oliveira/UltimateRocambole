// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyActor2.h"


// Sets default values
AMyActor2::AMyActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("BlockAll");


	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor2::Tick( float DeltaTime )
{

	Super::Tick(DeltaTime);
	FVector LocalizacaoAtual = GetActorLocation();
	float Range = 5.0f;

	if (Front && Cont < 120) {
		LocalizacaoAtual.X += Range;
		Cont++;
		if (Cont == 120) {
			Front = false;
			Back = true;
		}
	}

	if (Back && Cont >= 120) {
		LocalizacaoAtual.X -= Range;
		Cont++;
		if (Cont == 240) {
			Back = false;
			Front = true;
			Cont = 0;
		}

	}


	RunningTime += DeltaTime;
	SetActorLocation(LocalizacaoAtual);

}





