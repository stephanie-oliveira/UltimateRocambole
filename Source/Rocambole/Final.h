// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Final.generated.h"

/**
 * 
 */
UCLASS()
class ROCAMBOLE_API AFinal : public AItem
{
	GENERATED_BODY()

public:

		FORCEINLINE bool GetObjetoRobson() const { return ObjetoRobson; }
		FORCEINLINE void AFinal::SetObjetoRobson(bool NewObjetoRobson) { ObjetoRobson = NewObjetoRobson; }

private:

		bool ObjetoRobson;
	
	
	
	
};
