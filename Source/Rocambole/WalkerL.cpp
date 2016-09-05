// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "WalkerL.h"
#include "Bomba.h"


// Sets default values
AWalkerL::AWalkerL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	//Root->OnComponentHit.AddDynamic(this, &AWalkerL::OnHit);

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AWalkerL::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkerL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector LocalizacaoAtual = GetActorLocation();
	float Range = 5.0f;



	if (Right && Cont >= 0) {
		LocalizacaoAtual.Y += Range;
		Cont++;
		if (Cont == 90) {
			Right = false;
			Up = true;
			//UE_LOG(LogTemp, Warning, TEXT("Right"));

		}
	}

	if (Up && Cont < 180) {
		LocalizacaoAtual.X += Range;
		Cont++;
		if (Cont == 180) {
			Up = false;
			Right2 = true;
			//UE_LOG(LogTemp, Warning, TEXT("Up"));

		}

	}

	if (Right2 && Cont < 330) {
		LocalizacaoAtual.Y += Range;
		Cont++;
		if (Cont == 330) {
			Right2 = false;
			Up2 = true;
			//UE_LOG(LogTemp, Warning, TEXT("Right 2"));

		}

	}


	if (Up2 && Cont < 410) {
		LocalizacaoAtual.X += Range;
		Cont++;
		if (Cont == 410) {
			Up2 = false;
			Left = true;
			//UE_LOG(LogTemp, Warning, TEXT("Up 2"));

		}

	}


	if (Left && Cont < 650) {
		LocalizacaoAtual.Y -= Range;
		Cont++;
		if (Cont == 650) {
			Left = false;
			Down = true;
			//UE_LOG(LogTemp, Warning, TEXT("Left"));


		}

	}

	if (Down && Cont < 820) {
		LocalizacaoAtual.X -= Range;
		Cont++;
		if (Cont == 820) {
			Down = false;
			Right = true;
			Cont = 0;
			//UE_LOG(LogTemp, Warning, TEXT("Down"));


		}

	}

	if (ContBomb == 0) {

		DropBomb();
	}

	if (ContBomb < 120) {
		ContBomb++;

	}

	if (ContBomb == 120) {
		ContBomb = 0;
	}
	

	RunningTime += DeltaTime;
	SetActorLocation(LocalizacaoAtual);

}


void AWalkerL::DropBomb() {

	//para fazer o spawn do objeto. manda parametros específicos de colisão, movimentação, etc
	FActorSpawnParameters SpawnParameters;

	//para saber em que level vai adicionar o objeto
	UWorld* World = GetWorld();

	if (World != nullptr) {

		//pega a rotação do mesh pra dropar o projétil virado pro lado da seta
		FRotator Rotation = MeshComp->GetComponentRotation();

		//parametros: localização do spawn, rotação do objeto, spawn parameters
		ABomba* Bomba = World->SpawnActor<ABomba>(GetActorLocation(), Rotation, SpawnParameters);

		//if (Proj != nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("SPAUNO KRAI"));
		//}

	}


}




