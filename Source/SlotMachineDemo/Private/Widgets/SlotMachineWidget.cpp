﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachineDemo/Public/Widgets/SlotMachineWidget.h"

void USlotMachineWidget::NativeConstruct()
{
	if ( SlotMachineType )
	{
		SlotMachine = NewObject< USlotMachine >( this, SlotMachineType );
		SlotMachine->Init();
	}

	SlotMachine->OnBetSizeChanged.AddDynamic( this, &USlotMachineWidget::OnBetSizeChanged );
	SlotMachine->OnNumSelectedLinesChanged.AddDynamic( this, &USlotMachineWidget::OnNumSelectedLinesChanged );
	
	Super::NativeConstruct();
}
