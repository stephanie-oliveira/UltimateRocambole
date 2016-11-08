// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "Robson.h"
#include "Final.h"

AMyHUD::AMyHUD() {
	static ConstructorHelpers::FObjectFinder<UFont>Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));

	if (Font.Succeeded()) {
		HUDFont = Font.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>TextureChave(TEXT("Texture2D'/Game/Textures/chave.chave'"));

	if (Font.Succeeded()) {
		Chave = TextureChave.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>TextureObjeto(TEXT("Texture2D'/Game/Textures/objeto.objeto'"));

	if (Font.Succeeded()) {
		Objeto = TextureObjeto.Object;
	}

	ConstructorHelpers::FObjectFinder<UTexture2D>
		PotionTexture(TEXT("Texture2D'/Game/Textures/potion.potion'"));
	if (PotionTexture.Succeeded()) {
		Potion = PotionTexture.Object;
	}
}

void AMyHUD::DrawHUD() {

	Super::DrawHUD();

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas-> SizeY);

	ARobson* Robson = Cast<ARobson>(UGameplayStatics::GetPlayerPawn(this, 0));


	//FString LifeString = FString::Printf(TEXT("%d / 10"), Robson->GetColect());

	//DrawText(LifeString, FColor::Red, 300, 50, HUDFont);

	if (Robson->GetChave()) {
		DrawTextureSimple(Chave, 100, 50, 1.0f, false);
	}

	if (Robson->GetObjeto()) {
		DrawTextureSimple(Objeto, 100, 100, 1.0f, false);
	}


	//desenho potion
	//DrawTextureSimple(Potion, ScreenDimensions.X - Potion->GetSizeX(), 50, 0.1f, false);

	//FString PotionAmount = FString::Printf(TEXT("X %d"), Robson->GetInventory().Num());
	
	//DrawText(PotionAmount, FColor::Red, ScreenDimensions.X - Potion->GetSizeX(), 50, HUDFont);





	//DrawTexture(MyTexture, 200, 150, Robson->GetLife(), MyTexture->GetSizeY(), 200, 200, Robson->GetLife(), MyTexture->GetSizeY(),FLinearColor::White, EBlendMode::BLEND_Opaque, 1.0, false, 1.0f, FVector2D::ZeroVector);

		



}



