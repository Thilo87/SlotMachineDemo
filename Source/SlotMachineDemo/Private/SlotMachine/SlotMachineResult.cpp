// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachine/SlotMachineResult.h"

TArray<TSubclassOf<USlotMachineLine>> USlotMachineResult::GetWonLines() const
{
	TArray< TSubclassOf< USlotMachineLine > > WonLines;
	
	for ( auto const& LineResult: LineResults )
		if ( LineResult.bHasWon )
			WonLines.Add( LineResult.LineType );
	
	return WonLines;
}
