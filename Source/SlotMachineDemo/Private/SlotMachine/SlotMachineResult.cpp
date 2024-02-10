// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotMachine/SlotMachineResult.h"

void USlotMachineResult::CalcLineResults()
{
	for ( int l = 0; l < SlotMachine->NumSelectedLines; ++l )
	{
		auto const& Line = SlotMachine->Lines[ l ];

		FSlotMachineLineResult LineResult;
		LineResult.LineType = Line;
		
		for ( auto const& ElementType: SlotMachine->ElementTypes )
		{
			const int NumberOfElementTypeInLine = FindNumberOfElementTypeInLine( ElementType, Line );

			const USlotMachineElement* SlotMachineElementCDO = ElementType.GetDefaultObject();
			if ( const auto FoundPayout = SlotMachineElementCDO->Payout.Find( NumberOfElementTypeInLine ) )
			{
				const float PayoutForElementType = (*FoundPayout) * SlotMachine->BetSize;
				LineResult.OverallPayout += PayoutForElementType;
				Payout += PayoutForElementType;

				LineResult.bHasWon = true;
			}
		}

		LineResults.Add( LineResult );
	}
}

bool USlotMachineResult::IsElementInLine(int ElementColumnIndex, int ElementRowIndex,
                                         const TSubclassOf<USlotMachineLine>& Line)
{
	return Line.GetDefaultObject()->RowIndices[ ElementColumnIndex ] == ElementRowIndex;
}

void USlotMachineResult::FindLinesContainingElement(int ElementColumnIndex, int ElementRowIndex,
	TArray<TSubclassOf<USlotMachineLine>>& LinesContainingElement) const
{
	LinesContainingElement.Empty();
	
	for ( int l = 0; l < SlotMachine->NumSelectedLines; ++l )
	{
		auto const& Line = SlotMachine->Lines[ l ];
	
		if ( IsElementInLine( ElementColumnIndex, ElementRowIndex, Line ) )
			LinesContainingElement.Add( Line );
	}
}

int USlotMachineResult::FindNumberOfElementTypeInLine(const TSubclassOf<USlotMachineElement>& ElementType,
	const TSubclassOf<USlotMachineLine>& Line) const
{
	const USlotMachineLine* LineCDO = Line.GetDefaultObject();

	int NumElements = 0;
	for ( int i = 0; i < SlotMachine->NumColumns; ++i )
		if ( Elements[ i ].Elements[ LineCDO->RowIndices[ i ] ] == ElementType )
			++NumElements;

	return NumElements;
}

void USlotMachineResult::Init(USlotMachine* UsedSlotMachine)
{
	check( IsValid( UsedSlotMachine ) )
	
	SlotMachine = UsedSlotMachine;
	Elements = SlotMachine->GetAllColumns();
	
	CalcLineResults();
}

TArray<TSubclassOf<USlotMachineLine>> USlotMachineResult::GetWonLines() const
{
	TArray< TSubclassOf< USlotMachineLine > > WonLines;
	
	for ( auto const& LineResult: LineResults )
		if ( LineResult.bHasWon )
			WonLines.Add( LineResult.LineType );
	
	return WonLines;
}

bool USlotMachineResult::IsElementWinning(int ElementColumnIndex, int ElementRowIndex) const
{
	auto const& ElementType = GetElementType( ElementColumnIndex, ElementRowIndex );

	// first find all the lines that contain the element
	TArray< TSubclassOf< USlotMachineLine > > LinesContainingElement;
	FindLinesContainingElement( ElementColumnIndex, ElementRowIndex, LinesContainingElement );

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
