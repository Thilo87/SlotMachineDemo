// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachine.h"

void USlotMachine::RefillElements()
{
	Elements.Empty();

	for ( int j = 0; j < NumColumns; ++j )
	{
		Elements.Add( FSlotMachineColumn() );
		for ( int i = 0; i < ElementTypes.Num(); ++i )
			Elements[ i ].Elements.Add( ElementTypes[ i ] );
	}
}

void USlotMachine::ShuffleElements()
{
}

TArray<TObjectPtr<USlotMachineLine>> USlotMachine::FindWinningLines() const
{
}

void USlotMachine::Init()
{
	RefillElements();
}

float USlotMachine::GetTotalBet() const
{
	return Bet * NumSelectedLines;
}

void USlotMachine::SetBet(float NewBet)
{
	Bet = NewBet;
}

void USlotMachine::SetNumSelectedLines(int NewNumSelectedLines)
{
	NumSelectedLines = NewNumSelectedLines;
}

void USlotMachine::Spin(TArray<TObjectPtr<USlotMachineLine>>& WonLines, float& Payout)
{
	
}