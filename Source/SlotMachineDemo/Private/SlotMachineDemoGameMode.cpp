// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

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
