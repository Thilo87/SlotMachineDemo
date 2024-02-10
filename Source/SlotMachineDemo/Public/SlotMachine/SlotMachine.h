// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineElement.h"
#include "SlotMachineLine.h"
#include "UObject/Object.h"
#include "SlotMachine.generated.h"

class USlotMachineResult;
/**
 * Column of a slot machine with elements
 */
USTRUCT( BlueprintType, Category = "Slot Machine Column" )
struct FSlotMachineColumn
{
	GENERATED_BODY()

	/** Element types of this column */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine Column" )
	TArray< TSubclassOf< USlotMachineElement > > Elements;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSlotMachineBetSizeChanged, float, NewBetSize );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSlotMachineNumLinesChanged, int, NewNumLines );

/**
 * Main class of the slot machine. Handles all the backend stuff
 */
UCLASS( Blueprintable, Category = "Slot Machine" )
class SLOTMACHINEDEMO_API USlotMachine : public UObject
{
	GENERATED_BODY()
	
	/** Columns (and rows) of the slot machine. Access by Elements[ ColumnIndex ].Elements[ RowIndex ]. Does include currently invisible elements.
	 *	E.g. if possible elements are T, J, Q, K, A and a golden coin, but only 3 visible rows, there would be anyway 6 elements in each column.
	 */
	TArray< FSlotMachineColumn > Elements;
	
	/** Refills all elements */
	void RefillElements();
	
	/** Shuffles (spins) all elements instantly */
	void ShuffleElements();

	/** Randomize the order of the elements in the columns. Does not spin the column. */
	void RandomizeColumnsOrder();

public:
	void Init();

	
	/** Called when the bet size has been changed */
	UPROPERTY( BlueprintAssignable, Category = "Slot Machine|Delegates" )
	FSlotMachineBetSizeChanged OnBetSizeChanged;

	/** Called when the number of selected lines has been changed */
	UPROPERTY( BlueprintAssignable, Category = "Slot Machine|Delegates" )
	FSlotMachineNumLinesChanged OnNumSelectedLinesChanged;


	/** All lines of this slot machine the player can select */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Lines" )
	TArray< TSubclassOf< USlotMachineLine > > Lines;

	/** All possible elements in a column */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Elements" )
	TArray< TSubclassOf< USlotMachineElement > > ElementTypes;

	
	/** Number of visible rows of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Elements" )
	int NumVisibleRows = 3;

	/** Number of columns of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Elements" )
	int NumColumns = 5;

	
	/** Default number of selected lines */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Lines" )
	int NumSelectedLines = 1;

	
	/** Default amount of bet per line. Is multiplied with the payout of an element. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Bets" )
	float BetSize = 0.1f;

	/** Minimum allowed bet size */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Bets" )
	float MinBetSize = 0.1f;

	/** Maximum allowed bet size */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Bets" )
	float MaxBetSize = 2.f;

	/** Amount to increase the bet per step */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine|Properties|Bets" )
	float BetStepSize = 0.1f;



	/** Get all elements that are visible. The number of visible rows and columns is defined in other UPROPERTIES. */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Elements" )
	TArray< FSlotMachineColumn > GetVisibleColumns() const;
	
	/** Get all columns, including visible and invisible ones */
	UFUNCTION( BlueprintPure, Category = "Slot Machine|Elements" )
	const TArray< FSlotMachineColumn >& GetAllColumns() const { return Elements; }


	/*
	 *
	 * Lines
	 *
	 */

	/** Set number of selected lines */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Lines" )
	void SetNumSelectedLines( int NewNumSelectedLines, bool bTriggerEvents = true );

	/** Increases the number of lines */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Lines" )
	void IncreaseNumSelectedLines( bool bTriggerEvents = true );

	/** Decreases the number of lines */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Lines" )
	void DecreaseNumSelectedLines( bool bTriggerEvents = true );


	/*
	 *
	 * Bets
	 *
	 */
	
	/** Set amount of bet per line. Is multiplied with the payout of an element. */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Bets" )
	void SetBet( float NewBet, bool bTriggerEvents = true  );
	
	/** Increases the bet by the bet step size up to the max bet */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Bets" )
	void IncreaseBet( bool bTriggerEvents = true );

	/** Decreases the bet by the bet step size up to the min bet */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Bets" )
	void DecreaseBet( bool bTriggerEvents = true );

	/** Get the total bet */
	UFUNCTION( BlueprintPure, Category = "Slot Machine|Bets" )
	float GetTotalBet() const;

	
	/** Spins the machine. Returns the result. If bIsFreeSpin, it costs no money. If bCanEarnMoney, the won money is added to the bank account. */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine" )
	bool Spin( USlotMachineResult*& Result, bool bIsFreeSpin = false, bool bCanEarnMoney = true );

	/** Spins the machine NumRounds times with randomly selected lines and calculates an overall EV */
	UFUNCTION( BlueprintCallable, Category = "Slot Machine|Statistics" )
	void CalculateExpectedValue( int NumRounds, float& ExpectedValue );
};
