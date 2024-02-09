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
	for ( int i = 0; i < Elements.Num(); ++i )
	{
		auto& ColumnElements = Elements[ i ].Elements;
		
		// ElementTypes[ NewElementAtZero ] will be the first element in the new column
		const int NewElementAtZero = FMath::RandRange( 0, ElementTypes.Num() - 1 );

		// refill the turned column
		ColumnElements.Empty();
		for ( int j = 0; j < ElementTypes.Num(); ++j )
			ColumnElements.Add( ElementTypes[ ( j + NewElementAtZero ) % ElementTypes.Num() ] );
	}
}

void USlotMachine::FindWinningLines( TArray< TSubclassOf< USlotMachineLine > >& WinningLines, float& Payout ) const
{
	WinningLines.Empty();
	Payout = 0.f;
	
	TArray< FSlotMachineColumn > VisibleColumns = GetVisibleColumns();
	
	for ( const auto Line: Lines )
	{
		// we're saving and incrementing the number of same elements in the line here
		TMap< TSubclassOf< USlotMachineElement >, int > NumberOfSameElementsInLine;

		const USlotMachineLine* LineCDO = Line.GetDefaultObject();
		
		check( LineCDO->RowIndices.Num() == NumVisibleRows );
		check( VisibleColumns.Num() == NumVisibleRows );

		// calc number of same elements in line
		for ( int i = 0; i < NumVisibleRows; ++i )
		{
			const auto& Element = VisibleColumns[ i ].Elements[ LineCDO->RowIndices[ i ] ];
			const auto FoundElement = NumberOfSameElementsInLine.Find( Element );
			
			if ( !FoundElement )
				NumberOfSameElementsInLine.Add( Element, 1 );
			else
				( *FoundElement )++;
		}

		// summarize payout
		bool bHasAnyElementWon = false;
		for ( const auto NumberOfSameElements: NumberOfSameElementsInLine )
		{
			const USlotMachineElement* SlotMachineElementCDO = NumberOfSameElements.Key.GetDefaultObject();
			if ( const auto FoundPayout = SlotMachineElementCDO->Payout.Find( NumberOfSameElements.Value ) )
			{
				Payout += ( *FoundPayout ) * BetSize;
				bHasAnyElementWon = true;
			}
		}

		if ( bHasAnyElementWon )
			WinningLines.Add( Line );
	}
}

void USlotMachine::Init()
{
	RefillElements();
}

float USlotMachine::GetTotalBet() const
{
	return BetSize * NumSelectedLines;
}

TArray<FSlotMachineColumn> USlotMachine::GetVisibleColumns() const
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
	const float OldBet = BetSize;
	BetSize = NewBet;
	if ( OldBet != BetSize ) OnBetSizeChanged.Broadcast( NewBet );
}

void USlotMachine::SetNumSelectedLines(int NewNumSelectedLines)
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = NewNumSelectedLines;
	if ( OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NewNumSelectedLines );
}

void USlotMachine::IncreaseNumSelectedLines()
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = FMath::Min( NumSelectedLines + 1, Lines.Num() );
	if ( OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NumSelectedLines );
}

void USlotMachine::DecreaseNumSelectedLines()
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = FMath::Max( NumSelectedLines - 1, 1 );
	if ( OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NumSelectedLines );
}

void USlotMachine::IncreaseBet()
{
	const float OldBet = BetSize;
	BetSize = FMath::Min( BetSize + BetStepSize, MaxBetSize );
	if ( OldBet != BetSize ) OnBetSizeChanged.Broadcast( BetSize );
}

void USlotMachine::DecreaseBet()
{
	const float OldBet = BetSize;
	BetSize = FMath::Max( BetSize - BetStepSize, MinBetSize );
	if ( OldBet != BetSize ) OnBetSizeChanged.Broadcast( BetSize );
}

void USlotMachine::Spin(TArray<TSubclassOf<USlotMachineLine>>& WonLines, float& Payout)
{
	ShuffleElements();
	FindWinningLines( WonLines, Payout );
}
