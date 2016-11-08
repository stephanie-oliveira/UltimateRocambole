// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class ROCAMBOLE_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	UPROPERTY(EditAnywhere)
		UFont* HUDFont;

	UPROPERTY(EditAnywhere)
		UTexture2D* Chave;

	UPROPERTY(EditAnywhere)
		UTexture2D* Objeto;

	UPROPERTY(EditAnywhere)
		UTexture2D* Potion;

		virtual void DrawHUD() override;

	
	
};
