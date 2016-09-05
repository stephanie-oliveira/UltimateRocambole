// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Shooter.h"
#include "Spawn.h"
#include "Robson.h"



// Sets default values
AShooter::AShooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (ShootCont == 0) {

		Shoot();
	}

	if (ShootCont < 120) {
		ShootCont++;

	}

	if (ShootCont == 120) {
		ShootCont = 0;
	}
	

}

void AShooter::Shoot() {

	//para fazer o spawn do objeto. manda parametros específicos de colisão, movimentação, etc
	FActorSpawnParameters SpawnParameters;

	//para saber em que level vai adicionar o objeto
	UWorld* World = GetWorld();

	if (World != nullptr) {

		//pega a rotação do mesh pra dropar o projétil virado pro lado da seta
		FRotator Rotation = MeshComp->GetComponentRotation();

		//parametros: localização do spawn, rotação do objeto, spawn parameters
		ASpawn* Proj = World->SpawnActor<ASpawn>(GetActorLocation(), Rotation, SpawnParameters);

		//if (Proj != nullptr) {
			//UE_LOG(LogTemp, Warning, TEXT("SPAUNO KRAI"));
		//}

	}


}


void AShooter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		ASpawn* Proj = Cast<ASpawn>(OtherActor);


		//UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());
	}

}

