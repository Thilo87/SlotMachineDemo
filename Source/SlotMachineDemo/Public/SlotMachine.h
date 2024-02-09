// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineElement.h"
#include "SlotMachineLine.h"
#include "UObject/Object.h"
#include "SlotMachine.generated.h"

USTRUCT()
struct FSlotMachineColumn
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< TSubclassOf< USlotMachineElement > > Elements;
};

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
	
	// TArray< TObjectPtr< USlotMachineLine > > FindWinningLines() const;

public:
	void Init();

	/** All lines of this slot machine the player can select */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineLine > > Lines;

	/** All elements in the defined order in a column */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineElement > > ElementTypes;

	/** Number of rows of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumRows = 5;

	/** Number of columns of this slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumColumns = 5;


	/** Default number of selected lines */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int NumSelectedLines = 1;

	/** Default amount of bet per line. Is multiplied with the payout of an element. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float Bet = 10.f;
	

	/** Get the total bet */
	UFUNCTION( BlueprintPure )
	float GetTotalBet() const;

	/** Set amount of bet per line. Is multiplied with the payout of an element. */
	UFUNCTION( BlueprintCallable )
	void SetBet( float NewBet );

	/** Set number of selected lines */
	UFUNCTION( BlueprintCallable )
	void SetNumSelectedLines( int NewNumSelectedLines );
	
	/** Spins the machine. Returns the won lines and the payout. */
	UFUNCTION( BlueprintCallable )
	void Spin( TArray< USlotMachineLine* >& WonLines, float& Payout );
};
