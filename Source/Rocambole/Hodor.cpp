// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Hodor.h"
#include "Robson.h"



// Sets default values
AHodor::AHodor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshDoor(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));

	if (MeshDoor.Succeeded()) {
		Door->SetStaticMesh(MeshDoor.Object);
	}

	RootComponent = Door;

}

// Called when the game starts or when spawned
void AHodor::BeginPlay()
{
	Super::BeginPlay();

	StartYaw = Door->GetComponentRotation().Yaw;
	
}

// Called every frame
void AHodor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator Rotation = Door->GetComponentRotation();
	
	ARobson* Robson = Cast<ARobson>(UGameplayStatics::GetPlayerPawn(this, 0));



	if (Open && (Rotation.Yaw + 180.0f) + 1.0f < (StartYaw + 90.0f)) {
		Rotation.Yaw -= 1.0f;
	}
	else if (!Open && (Rotation.Yaw + 180.0f) - 1.0f > StartYaw) {
		Rotation.Yaw += 1.0f;
		Robson->SetChave(false);


	}

	Door->SetWorldRotation(Rotation);

}
