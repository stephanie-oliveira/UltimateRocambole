// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Bomba.h"


// Sets default values
ABomba::ABomba()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	//inidica tamanho inicial
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);

	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MeshComp->AttachTo(RootComponent);

	//definir tempo de vida
	InitialLifeSpan = 2.0f;


}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomba::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



