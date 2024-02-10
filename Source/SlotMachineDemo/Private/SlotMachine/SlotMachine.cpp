// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "SlotMachine/SlotMachine.h"

#include "SlotMachineDemoGameMode.h"
#include "Algo/RandomShuffle.h"

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
		auto ColumnElementsCopy = Elements[ i ].Elements;
		auto& ColumnElements = Elements[ i ].Elements;
		
		// ElementTypes[ NewElementAtZero ] will be the first element in the new column
		const int NewElementAtZero = FMath::RandRange( 0, ElementTypes.Num() - 1 );

		// refill the turned column
		ColumnElements.Empty();
		for ( int j = 0; j < ElementTypes.Num(); ++j )
			ColumnElements.Add( ColumnElementsCopy[ ( j + NewElementAtZero ) % ElementTypes.Num() ] );
	}
}

void USlotMachine::RandomizeColumnsOrder()
{
	for ( int i = 0; i < Elements.Num(); ++i )
		Algo::RandomShuffle( Elements[ i ].Elements );
}

void USlotMachine::FindWinningLines( USlotMachineResult*& Result ) const
{
	TArray< FSlotMachineColumn > VisibleColumns = GetVisibleColumns();

	Result->Elements.Empty();
	for ( auto const& VisibleColumn: VisibleColumns )
	{
		FSlotMachineColumnResult ColumnResult;
		for ( auto const& VisibleElement: VisibleColumn.Elements )
		{
			FSlotMachineElementResult ElementResult;
			ElementResult.ElementType = VisibleElement;
			
			ColumnResult.Elements.Add( ElementResult );
		}
		
		Result->Elements.Add( ColumnResult );
	}
	
	for ( int j = 0; j < VisibleColumns.Num(); ++j )
		for ( int i = 0; i < VisibleColumns[ j ].Elements.Num(); ++i )
			FindLinesContainingElement( j, i, Result->Elements[ j ].Elements[ i ].Lines );
	
	for ( int l = 0; l < NumSelectedLines; ++l )
	{
		auto const& Line = Lines[ l ];

		FSlotMachineLineResult LineResult;
		LineResult.LineType = Line;
		
		for ( auto const& ElementType: ElementTypes )
		{
			const int NumberOfElementTypeInLine = FindNumberOfElementTypeInLine( ElementType, Line );

			const USlotMachineElement* SlotMachineElementCDO = ElementType.GetDefaultObject();
			if ( const auto FoundPayout = SlotMachineElementCDO->Payout.Find( NumberOfElementTypeInLine ) )
			{
				LineResult.OverallPayout += (*FoundPayout) * NumberOfElementTypeInLine * BetSize;
				Result->Payout += LineResult.OverallPayout;

				LineResult.bHasWon = true;
			}
		}

		Result->LineResults.Add( LineResult );
	}
}

bool USlotMachine::IsElementInLine(int ElementColumnIndex, int ElementRowIndex, const TSubclassOf<USlotMachineLine>& Line) const
{
	const USlotMachineLine* LineCDO = Line.GetDefaultObject();
			
	if ( LineCDO->RowIndices[ ElementColumnIndex ] == ElementRowIndex )
		return true;

	return false;
}

void USlotMachine::FindLinesContainingElement(int ElementColumnIndex, int ElementRowIndex,
	TArray<TSubclassOf<USlotMachineLine>>& LinesContainingElement) const
{
	LinesContainingElement.Empty();
	
	for ( int l = 0; l < NumSelectedLines; ++l )
	{
		auto const& Line = Lines[ l ];
	
		if ( IsElementInLine( ElementColumnIndex, ElementRowIndex, Line ) )
			LinesContainingElement.Add( Line );
	}
}

int USlotMachine::FindNumberOfElementTypeInLine(const TSubclassOf<USlotMachineElement>& ElementType,
	const TSubclassOf<USlotMachineLine>& Line) const
{
	// TODO: optimize?
	TArray< FSlotMachineColumn > VisibleColumns = GetVisibleColumns();
	const USlotMachineLine* LineCDO = Line.GetDefaultObject();

	int NumElements = 0;
	for ( int i = 0; i < NumColumns; ++i )
		if ( VisibleColumns[ i ].Elements[ LineCDO->RowIndices[ i ] ] == ElementType )
			++NumElements;

	return NumElements;
}

void USlotMachine::Init()
{
	RefillElements();
	RandomizeColumnsOrder();
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

void USlotMachine::SetBet(float NewBet, bool bTriggerEvents)
{
	const float OldBet = BetSize;
	BetSize = NewBet;
	if ( bTriggerEvents && OldBet != BetSize ) OnBetSizeChanged.Broadcast( NewBet );
}

void USlotMachine::SetNumSelectedLines(int NewNumSelectedLines, bool bTriggerEvents)
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = NewNumSelectedLines;
	if ( bTriggerEvents && OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NewNumSelectedLines );
}

void USlotMachine::IncreaseNumSelectedLines(bool bTriggerEvents)
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = FMath::Min( NumSelectedLines + 1, Lines.Num() );
	if ( bTriggerEvents && OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NumSelectedLines );
}

void USlotMachine::DecreaseNumSelectedLines(bool bTriggerEvents)
{
	const int OldNumSelectedLines = NumSelectedLines;
	NumSelectedLines = FMath::Max( NumSelectedLines - 1, 1 );
	if ( bTriggerEvents && OldNumSelectedLines != NumSelectedLines ) OnNumSelectedLinesChanged.Broadcast( NumSelectedLines );
}

void USlotMachine::IncreaseBet(bool bTriggerEvents)
{
	const float OldBet = BetSize;
	BetSize = FMath::Min( BetSize + BetStepSize, MaxBetSize );
	if ( bTriggerEvents && OldBet != BetSize ) OnBetSizeChanged.Broadcast( BetSize );
}

void USlotMachine::DecreaseBet(bool bTriggerEvents)
{
	const float OldBet = BetSize;
	BetSize = FMath::Max( BetSize - BetStepSize, MinBetSize );
	if ( bTriggerEvents && OldBet != BetSize ) OnBetSizeChanged.Broadcast( BetSize );
}

bool USlotMachine::Spin(USlotMachineResult*& Result, bool bIsFreeSpin)
{
	const ASlotMachineDemoGameMode* GameMode = Cast< ASlotMachineDemoGameMode >( GetWorld()->GetAuthGameMode() );
	if ( !GameMode )
		return false;
	
	if ( !bIsFreeSpin && ( !IsValid( GameMode->GetBank() ) || !GameMode->GetBank()->AddToBalance( -GetTotalBet() ) ) )
		return false;
	
	ShuffleElements();

	Result = NewObject< USlotMachineResult >();
	FindWinningLines( Result );

	if ( !bIsFreeSpin )
		GameMode->GetBank()->AddToBalance( Result->Payout );
	
	return true;
}

void USlotMachine::CalculateExpectedValue(int NumRounds, float& ExpectedValue)
{
	const int OldNumSelectedLines = NumSelectedLines;
	const float OldBetSize = BetSize;
	
	float OverallPayout = 0.f;
	float OverallInvestments = 0.f;
	for ( int i = 0; i < NumRounds; ++i )
	{
		// select a random number of lines
		const int RandomNumSelectedLines = FMath::RandRange( 1, Lines.Num() );
		SetNumSelectedLines( RandomNumSelectedLines, false );

		// increase or decrease bet size
		if ( static_cast< bool >( FMath::RandRange( 0, 1 ) ) )
			IncreaseBet( false );
		else
			DecreaseBet( false );

		// simulate a spin
		TArray< TSubclassOf< USlotMachineLine > > WonLines;

		USlotMachineResult* Result;
		Spin( Result, true );
		
		OverallPayout += Result->Payout;
		OverallInvestments += GetTotalBet();
	}
	
	// reset number of selected lines and bet size
	SetNumSelectedLines( OldNumSelectedLines, false );
	SetBet( OldBetSize, false );
	
	ExpectedValue = OverallPayout / OverallInvestments;
}

bool USlotMachine::IsWinningElement(int ColumnIndex, int RowIndex) const
{
	auto const& ElementType = GetElementType( ColumnIndex, RowIndex );

	// first find all the lines that contain the element
	TArray< TSubclassOf< USlotMachineLine > > LinesContainingElement;
	FindLinesContainingElement( ColumnIndex, RowIndex, LinesContainingElement );

	// go through all lines containing the element
	for ( auto const& LineType: LinesContainingElement )
	{
		// find the number of same elements in the line
		const int NumberOfElementTypeInLine = FindNumberOfElementTypeInLine( ElementType, LineType );

		// find the payout for the number of elements - if there is one, it's winning
		if ( ElementType.GetDefaultObject()->Payout.Find( NumberOfElementTypeInLine ) )
			return true;
	}

	return false;
}
