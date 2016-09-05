// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "Robson.h"

AMyHUD::AMyHUD() {
	static ConstructorHelpers::FObjectFinder<UFont>Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));

	if (Font.Succeeded()) {
		HUDFont = Font.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>Texture(TEXT("Texture2D'/Game/Textures/heart.heart'"));

	if (Font.Succeeded()) {
		MyTexture = Texture.Object;
	}
}

void AMyHUD::DrawHUD() {

	Super::DrawHUD();

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas-> SizeY);

	ARobson* Robson = Cast<ARobson>(

		UGameplayStatics::GetPlayerPawn(this, 0));

	FString LifeString = FString::Printf(TEXT("%d / 10"), Robson->GetColect());

	DrawText(LifeString, FColor::Red, 300, 50, HUDFont);

	if (Robson->GetLife() >= 1) {
		DrawTextureSimple(MyTexture, 100, 50, 1.0f, false);

	}

	if (Robson->GetLife() >= 3) {
		DrawTextureSimple(MyTexture, 150, 50, 1.0f, false);

	}

	if (Robson->GetLife() == 3) {
		DrawTextureSimple(MyTexture, 200, 50, 1.0f, false);

	}




	//DrawTexture(MyTexture, 200, 150, Robson->GetLife(), MyTexture->GetSizeY(), 200, 200, Robson->GetLife(), MyTexture->GetSizeY(),
	//	FLinearColor::White, EBlendMode::BLEND_Opaque, 1.0, false, 1.0f, FVector2D::ZeroVector);

		



}



