// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachineDemoGameMode.h"

void ASlotMachineDemoGameMode::BeginPlay()
{
	if ( BankType )
	{
		Bank = NewObject< UBank >( this, BankType );
		Bank->Init();
	}
	else
		UE_LOG( LogInit, Warning, TEXT( "No bank class in game mode selected." ) );
	
	Super::BeginPlay();
}
