// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Robson.h"
#include "Spawn.h"
#include "CogumeloDoMau.h"
#include "Item.h"
#include "Alavanca.h"
#include "Objeto.h"
#include "Chave.h"
#include "Final.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"




// Sets default values
ARobson::ARobson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Permite que haja sobreposição
	GetCapsuleComponent()->bGenerateOverlapEvents = true;


	//Cria forma do personagem
	//MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->AttachTo(GetCapsuleComponent());

	//usando animação em bp
	ConstructorHelpers::FObjectFinder<USkeletalMesh>SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -80.0f));
	GetMesh()->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));

	//opção de animation mode
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimObj(TEXT("AnimBlueprint'/Game/BluePrint/WalkBP.WalkBP'"));

	if (AnimObj.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimObj.Object->GetAnimBlueprintGeneratedClass());
	}

	//alterar atributos
	
	GetCharacterMovement()->MaxWalkSpeed = 400;

	//TELA PAUSE

	ConstructorHelpers::FClassFinder<UUserWidget>Widget(TEXT("WidgetBlueprint'/Game/BluePrint/Pause.Pause_C'"));

	if (Widget.Succeeded()) {
		UserWidget = Widget.Class;
	}

	//SOM

	ConstructorHelpers::FObjectFinder<USoundCue>SoundCue(TEXT("SoundCue'/Game/Audios/shoot_Cue.shoot_Cue'"));

	if (SoundCue.Succeeded()) {
		FireSound = SoundCue.Object;
	}

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	AudioComp->AttachTo(GetMesh());

	//Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	//distancia entre o player e a camera / ligação entre o player e a camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	PlayerCamera->AttachTo(CameraBoom);

	/*ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->AttachTo(GetMesh());*/

	//Seta velocidade do personagem
	GetCharacterMovement()->MaxWalkSpeed = 800;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//área de colisão com coletáveis
	CollectCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollectColision"));
	CollectCollisionComp->InitSphereRadius(200.0f);
	CollectCollisionComp->AttachTo(RootComponent);


	ConstructorHelpers::FObjectFinder<UAnimSequence>AnimJumpLoad(TEXT("AnimSequence'/Game/AnimStarterPack/Jump_From_Stand.Jump_From_Stand'"));

	if (AnimJumpLoad.Succeeded()) {
		JumpAnim = AnimJumpLoad.Object;
	}

	//AUTORIZA AÇÕES A SEREM REPLICADAS
	bReplicates = true;
	bReplicateMovement = true;

}

// Called when the game starts or when spawned
void ARobson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobson::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode &&GetCharacterMovement()->IsMovingOnGround()) {

		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}

}

// Called to bind functionality to input
void ARobson::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//mapeamento de entrada criado no editor, qual elemento que ele vai movimentar, qual método será utilizado quando chamar isso(endereço de memória onde foi armazenado)
	InputComponent->BindAxis("MoveForward", this, &ARobson::MoveForward);
	InputComponent->BindAxis("MoveSides", this, &ARobson::MoveSides);
	InputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);


	//mapeamento de entrada criado no editor, estado da tecla(pressionada), qual elemento que ele vai movimentar, qual método será utilizado quando chamar isso(endereço de memória onde foi armazenado)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARobson::Jump);
	//quando solta a tecla
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Run", IE_Pressed, this, &ARobson::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &ARobson::StopRun);

	//dropa esfera
	InputComponent->BindAction("Drop", IE_Pressed, this, &ARobson::DropSphere);

	//coletar item na área
	InputComponent->BindAction("Collect", IE_Pressed, this, &ARobson::OnCollect);

	InputComponent->BindAction("Pause", IE_Pressed, this, &ARobson::Pause);
	InputComponent->BindAction("Show", IE_Pressed, this, &ARobson::ShowPontuacao);





}

//Movimentação frente/trás
void ARobson::MoveForward(float Value) {

	//(x,y,z)
	//FVector Forward(1, 0, 0);
	//forward, value do parametro
	//AddMovementInput(Forward, Value);

	if (Controller != nullptr && Value != 0) {

		FRotator Rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround()) {
			Rotation.Pitch = 0.0f;
		}

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}


}

//Movimentação lados
void ARobson::MoveSides(float Value) {
	//(x,y,z)
	//FVector Forward(0, 1, 0);
	//forward, value do parametro
	//AddMovementInput(Forward, Value);

	if (Controller != nullptr && Value != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}

}

void ARobson::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 1400;

}
void ARobson::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800;

}

//Encapsulamento da variável Life
void ARobson::SetLife(int NewLife) {
	Life = NewLife;
}

int ARobson::GetLife() {
	return Life;

}

void ARobson::SetCont(int NewCont) {
	Cont = NewCont;
}

int ARobson::GetCont() {
	return Cont;

}

void ARobson::SetColect(int NewColect) {
	Colect = NewColect;
}

int ARobson::GetColect() {
	return Colect;

}



void ARobson::GameOver() {

	if (Life <= 0) {
		//Pega a posição inicial
		FVector InitialLocation(-660.0f, 320.0f, 2320.0f);
		//Seta a vida de volta a 3 pra não morrer infinitamente
		Life = 3;
		//Seta a posição do ator para a inicial
		SetActorLocation(InitialLocation);
	}

}

void ARobson::DropSphere() {

	DropSphereServer_Implementation();


}

//PARA DEFINIR QUE O MÉTODO SERÁ EXECUTADO A APRTIR DO SERVER

void ARobson::DropSphereServer_Implementation() {


	//para fazer o spawn do objeto. manda parametros específicos de colisão, movimentação, etc
	FActorSpawnParameters SpawnParameters;

	//para saber em que level vai adicionar o objeto
	UWorld* World = GetWorld();

	if (World != nullptr) {

		//pega a rotação do mesh pra dropar o projétil virado pro lado da seta
		FRotator Rotation = GetMesh()->GetComponentRotation();

		//parametros: localização do spawn, rotação do objeto, spawn parameters
		ASpawn* Proj = World->SpawnActor<ASpawn>(GetActorLocation(), Rotation, SpawnParameters);
		//PARA EXECUTAR O SOM
		AudioComp->SetSound(FireSound);
		AudioComp->Play();


		if (Proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("SPAWN"));
		}

	}

}
bool ARobson::DropSphereServer_Validate() {
	return true;
}


void ARobson:: Turn(float Value) {

	//girar sobre o eixo z
	//AddControllerYawInput(Value);

	FRotator NewRotation = GetMesh()->GetComponentRotation();
	NewRotation.Yaw += Value;
	GetMesh()->SetWorldRotation(NewRotation);
}

//void AWalker::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
//
		//AWalker* Walker = Cast<AWalker>(OtherActor);


		//UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());

void ARobson::OnCollect() {

	//lista dos atores coletados
	TArray<AActor*>AtoresColetados;

	//para coletar, pega os atores e joga pra lista
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	AFinal* PontoFinal = Cast<AFinal>(UGameplayStatics::GetPlayerPawn(this, 0));

	//passa por todos os itens e confere se são do tipo Item
	for (int i = 0; i < AtoresColetados.Num(); i++) {

		
		if (AtoresColetados[i]->IsA(AItem::StaticClass())) {
			//cria um objeto AItem e faz um cast de actor pra AItem
			AItem* ItemColetado = Cast <AItem>(AtoresColetados[i]);

			//adiciona o ItemColetado criado ao inventário
			Inventory.Add(ItemColetado);

			
			//caso colete a chave
			if (AtoresColetados[i]->IsA(AChave::StaticClass())) {
				Chave = true;
				//destrói o item coletado
				ItemColetado->Destroy();
			}

			if (AtoresColetados[i]->IsA(AObjeto::StaticClass())) {
				Objeto = true;
				ItemColetado->Destroy();

			}

			if (AtoresColetados[i]->IsA(AFinal::StaticClass())) {
				Final = true;
				Objeto = false;
			}


			UE_LOG(LogTemp, Warning, TEXT("Inventário: %d"), Inventory.Num());
		}
		else if (AtoresColetados[i]->IsA(AAlavanca::StaticClass())) {
			AAlavanca* Alavanca = Cast<AAlavanca>(AtoresColetados[i]);
			Alavanca->OnPressed();

		}
	}

	if (Final) {
		Objeto = false;
	}
}

void ARobson::Jump() {
	Super::Jump();

	if (JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
	}
}

void ARobson::Pause() {

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController != nullptr && UserWidget != NULL) {
			PlayerController->SetPause(true);
			UUserWidget *UserW = UWidgetBlueprintLibrary::Create(World, UserWidget, PlayerController);
			if (UserW != nullptr) {
				UserW->AddToViewport();
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}

void ARobson::ShowPontuacao() {
	UE_LOG(LogTemp, Warning, TEXT("Pontuacao: %d"), Pontuacao);
}





