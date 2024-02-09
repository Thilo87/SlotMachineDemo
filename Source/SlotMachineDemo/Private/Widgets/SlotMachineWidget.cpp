// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "SlotMachineDemo/Public/Widgets/SlotMachineWidget.h"
#include "Bank.h"

#include "SlotMachineDemoGameMode.h"

void USlotMachineWidget::NativeConstruct()
{
	if ( SlotMachineType )
	{
		SlotMachine = NewObject< USlotMachine >( this, SlotMachineType );
		SlotMachine->Init();
		
		SlotMachine->OnBetSizeChanged.AddDynamic( this, &USlotMachineWidget::OnBetSizeChanged );
		SlotMachine->OnNumSelectedLinesChanged.AddDynamic( this, &USlotMachineWidget::OnNumSelectedLinesChanged );

		if ( const ASlotMachineDemoGameMode* GameMode = Cast< ASlotMachineDemoGameMode >( GetWorld()->GetAuthGameMode() ) )
			if ( UBank* Bank = GameMode->GetBank() )
				Bank->OnBankBalanceChanged.AddDynamic( this, &USlotMachineWidget::OnBankBalanceChanged );
	}
	else
		UE_LOG( LogInit, Warning, TEXT("No slot machine type in the slot machine widget selected.") );

	Super::NativeConstruct();
}
