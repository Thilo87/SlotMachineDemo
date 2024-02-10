// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "SlotMachine/SlotMachine.h"

#include "SlotMachineDemoGameMode.h"
#include "Algo/RandomShuffle.h"
#include "SlotMachine/SlotMachineResult.h"

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

void USlotMachine::Init()
{
	RefillElements();
	RandomizeColumnsOrder();
}

float USlotMachine::GetTotalBet() const
{
	return BetSize * NumSelectedLines;
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

bool USlotMachine::Spin(USlotMachineResult*& Result, bool bIsFreeSpin, bool bCanEarnMoney)
{
	const ASlotMachineDemoGameMode* GameMode = Cast< ASlotMachineDemoGameMode >( GetWorld()->GetAuthGameMode() );
	if ( !GameMode )
		return false;
	
	if ( !IsValid( GameMode->GetBank() ) )
		return false;
	
	if ( !bIsFreeSpin )
		if ( !GameMode->GetBank()->AddToBalance( -GetTotalBet() ) )
			return false;

	// this actually spins the columns
	ShuffleElements();

	// create result. All calculations are made in there.
	Result = NewObject< USlotMachineResult >();
	Result->Init( this );
	
	if ( bCanEarnMoney )
		GameMode->GetBank()->AddToBalance( Result->GetPayout() );
	
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
		USlotMachineResult* Result;
		Spin( Result, true, false );
		
		OverallPayout += Result->GetPayout();
		OverallInvestments += GetTotalBet();
	}
	
	// reset number of selected lines and bet size
	SetNumSelectedLines( OldNumSelectedLines, false );
	SetBet( OldBetSize, false );
	
	ExpectedValue = OverallPayout / OverallInvestments;
}
