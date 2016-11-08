// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Robson.generated.h"

UCLASS()
class ROCAMBOLE_API ARobson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobson();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//get e set do Life
	void SetLife(int NewLife);
	int GetLife();

	//get e set do contador
	void SetCont(int NewCont);
	int GetCont();

	//get e set do Colect
	void SetColect(int NewColect);
	int GetColect();

	//Voltar pro início
	void GameOver();

	FORCEINLINE TArray<class AItem*> GetInventory() const { return Inventory; }

	FORCEINLINE int GetPontuacao() const { return Pontuacao; }
	FORCEINLINE void ARobson::SetPontuacao(int NewPontuacao) { Pontuacao = NewPontuacao; }

	FORCEINLINE bool GetChave() const { return Chave; }
	FORCEINLINE void ARobson::SetChave(bool NewChave) { Chave = NewChave; }

	FORCEINLINE bool GetObjeto() const { return Objeto; }
	FORCEINLINE void ARobson::SetObjeto(bool NewObjeto) { Objeto = NewObjeto; }

	FORCEINLINE bool GetFinal() const { return Final; }
	FORCEINLINE void ARobson::SetFinal(bool NewFinal) { Final = NewFinal; }

	virtual void Jump() override;


private:

	int cont = 0;

	//coletar potion
	USphereComponent* CollectCollisionComp;
	//lista para coletagem de poção
	TArray<class AItem*> Inventory;
	

	//Forma do personagem
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
		//movimentação / angulo da câmera
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		//setinha
		UArrowComponent* ArrowComp;

	//movimentação com WASD
	void MoveForward(float Value);
	void MoveSides(float Value);
	//Correr
	void StartRun();
	void StopRun();

	void OnCollect();

	void Pause();

	//Vida
	UPROPERTY(EditAnywhere)
	int Life = 3;

	UPROPERTY(EditAnywhere)
	int Cont = 0;

	UPROPERTY(EditAnywhere)
	int Colect = 0;


	//SOM

	USoundCue* FireSound;
	UAudioComponent* AudioComp;

	TSubclassOf<class UUserWidget> UserWidget;


	void DropSphere();

	void Turn(float Value);

	//UFUNCTION()
		//void OnHit(UPrimitiveComponent* HitComponen, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit);

	UPROPERTY(EditAnywhere)

		UAnimSequence* JumpAnim;

	//PARA DEFINIR QUE O MÉTODO SERÁ EXECUTADO A APRTIR DO SERVER

	UFUNCTION(Reliable, Server, WithValidation)

		void DropSphereServer();
		void DropSphereServer_Implementation();
		bool DropSphereServer_Validate();
	
		UPROPERTY(EditAnywhere)
		int Pontuacao;

	void ShowPontuacao();

	bool Chave;
	bool Objeto;
	bool Final;

	
};
