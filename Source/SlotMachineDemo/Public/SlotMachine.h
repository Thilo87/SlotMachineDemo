// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineElement.h"
#include "SlotMachineLine.h"
#include "UObject/Object.h"
#include "SlotMachine.generated.h"

USTRUCT( BlueprintType )
struct FSlotMachineColumn
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineElement > > Elements;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSlotMachineBetSizeChanged, float, NewBetSize );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSlotMachineNumLinesChanged, int, NewNumLines );

/**
 * 
 */
UCLASS( Blueprintable )
class SLOTMACHINEDEMO_API USlotMachine : public UObject
{
	GENERATED_BODY()
	
	/** Columns (and rows) of the slot machine. Access by Elements[ ColumnIndex ].Elements[ RowIndex ]. Does include currently invisible elements.
	 *	E.g. if possible elements are T, J, Q, K, A and a golden coin, but only 3 visible rows, there would be anyway 6 elements in each column.
	 */
	TArray< FSlotMachineColumn > Elements;
	
	/** Refills all elements */
	void RefillElements();

	/** Get element at the specified row and column */
	TSubclassOf< USlotMachineElement > GetElement( int RowIndex, int ColumnIndex ) const { return Elements[ RowIndex ].Elements[ ColumnIndex ]; }
	
	/** Shuffles (spins) all elements instantly */
	void ShuffleElements();
	
	void FindWinningLines( TArray< TSubclassOf< USlotMachineLine > >& WinningLines, float& Payout ) const;

public:
	void Init();

	UPROPERTY( BlueprintAssignable )
	FSlotMachineBetSizeChanged OnBetSizeChanged;

	UPROPERTY( BlueprintAssignable )
	FSlotMachineNumLinesChanged OnNumSelectedLinesChanged;


	/** All lines of this slot machine the player can select */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineLine > > Lines;

	/** All elements in the defined order in a column */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineElement > > ElementTypes;

	/** Number of visible rows of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumVisibleRows = 3;

	/** Number of columns of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumColumns = 5;


	/** Default number of selected lines */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumSelectedLines = 1;

	/** Default amount of bet per line. Is multiplied with the payout of an element. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float BetSize = 0.1f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float MinBetSize = 0.1f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float MaxBetSize = 2.f;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float BetStepSize = 0.1f;

	/** Get the total bet */
	UFUNCTION( BlueprintPure )
	float GetTotalBet() const;

	/** Get all elements that are visible. The number of visible rows and columns is defined in other UPROPERTIES. */
	UFUNCTION( BlueprintCallable )
	TArray< FSlotMachineColumn > GetVisibleColumns() const;

	/** Set amount of bet per line. Is multiplied with the payout of an element. */
	UFUNCTION( BlueprintCallable )
	void SetBet( float NewBet );

	/** Set number of selected lines */
	UFUNCTION( BlueprintCallable )
	void SetNumSelectedLines( int NewNumSelectedLines );

	UFUNCTION( BlueprintCallable )
	void IncreaseNumSelectedLines();
	
	UFUNCTION( BlueprintCallable )
	void DecreaseNumSelectedLines();

	UFUNCTION( BlueprintCallable )
	void IncreaseBet();
	
	UFUNCTION( BlueprintCallable )
	void DecreaseBet();
	
	/** Spins the machine. Returns the won lines and the payout. */
	UFUNCTION( BlueprintCallable )
	void Spin( TArray< TSubclassOf< USlotMachineLine > >& WonLines, float& Payout );
};
