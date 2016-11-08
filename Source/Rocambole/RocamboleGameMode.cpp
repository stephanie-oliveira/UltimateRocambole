// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "RocamboleGameMode.h"
#include "MyHUD.h"
#include "Robson.h"
ARocamboleGameMode::ARocamboleGameMode()  {

	HUDClass = AMyHUD::StaticClass();

	DefaultPawnClass = ARobson::StaticClass();

}




