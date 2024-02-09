// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachine.h"

void USlotMachine::RefillElements()
{
	Elements.Empty();

	for ( int j = 0; j < NumColumns; ++j )
	{
		Elements.Add( FSlotMachineColumn() );
		for ( int i = 0; i < ElementTypes.Num(); ++i )
			Elements[ j ].Elements.Add( ElementTypes[ i ] );
	}
}

void USlotMachine::ShuffleElements()
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

TArray<FSlotMachineColumn> USlotMachine::GetVisibleElements() const
{
	TArray< FSlotMachineColumn > VisibleElements;
	for ( int j = 0; j < FMath::Min( Elements.Num(), NumColumns ); ++j )
	{
		FSlotMachineColumn Column;
		for ( int i = 0; i < FMath::Min( Elements[ j ].Elements.Num(), NumVisibleRows ); ++i )
			Column.Elements.Add( Elements[ j ].Elements[ i ] );
		VisibleElements.Add( Column );
	}
	return VisibleElements;
}

void USlotMachine::SetBet(float NewBet)
{
	Bet = NewBet;
}

void USlotMachine::SetNumSelectedLines(int NewNumSelectedLines)
{
	NumSelectedLines = NewNumSelectedLines;
}

void USlotMachine::Spin(TArray<USlotMachineLine*>& WonLines, float& Payout)
{
	
}