// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachineDemo/Public/SlotMachineWidget.h"

void USlotMachineWidget::NativeConstruct()
{
	if ( SlotMachineType )
		SlotMachine = NewObject< USlotMachine >( this, SlotMachineType );
	
	Super::NativeConstruct();
}
