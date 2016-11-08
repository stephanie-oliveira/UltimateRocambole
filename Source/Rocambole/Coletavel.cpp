// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Coletavel.h"
#include "Robson.h"


// Sets default values
AColetavel::AColetavel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}

	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MeshComp->OnComponentHit.AddDynamic(this, &AColetavel::OnHit);
	MeshComp->AttachTo(RootComponent);

	bReplicates = true;

}

// Called when the game starts or when spawned
void AColetavel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColetavel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AColetavel::OnHit(UPrimitiveComponent* HitComponen, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	if (OtherComp != nullptr  && OtherComp->IsA(ARobson::StaticClass()) && OtherComp != nullptr) {
		ARobson* Robson = Cast<ARobson>(OtherActor);
	
		Robson->SetPontuacao(Robson->GetPontuacao() + 10);
		Destroy();

	}
}

