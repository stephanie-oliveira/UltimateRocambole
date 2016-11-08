// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Alavanca.h"
#include "Hodor.h"
#include "Robson.h"



// Sets default values
AAlavanca::AAlavanca()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Cria a área de colisão
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));


}

// Called when the game starts or when spawned
void AAlavanca::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlavanca::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAlavanca::OnPressed() {
	
	TArray<AActor*> Portas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHodor::StaticClass(), Portas);

	ARobson* Robson = Cast<ARobson>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Portas.Num() > 0) {
		AHodor* Porta = Cast<AHodor>(Portas[0]);
		if (Robson->GetChave()){

			if (Porta->IsOpen()) {
				Porta->SetOpen(false);

			}
			else {

				Porta->SetOpen(true);
			}

		}

	}


}
