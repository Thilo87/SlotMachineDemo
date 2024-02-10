// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachine.h"
#include "SlotMachineElement.h"
#include "SlotMachineLine.h"
#include "UObject/Object.h"
#include "SlotMachineResult.generated.h"

/*
 * Results for a specific line
 */
USTRUCT( BlueprintType )
struct FSlotMachineLineResult
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachineLine > LineType;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	bool bHasWon = false;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	float OverallPayout = 0.f;
};

/**
 * Class representing a result of a slot machine spin. Contains all information necessary for statistics etc. TODO: include slot machine properties
 */
UCLASS( BlueprintType )
class SLOTMACHINEDEMO_API USlotMachineResult : public UObject
{
	GENERATED_BODY()

	/** Results of a specific line */
	TArray< FSlotMachineLineResult > LineResults;

	/** Overall payout of the result */
	float Payout = 0.f;

	/** State of all columns/elements (copy) of the used slot machine */
	TArray< FSlotMachineColumn > Elements;

	
	// TODO: copy over slot machine properties. Because the slot machine object could change later, it shouldn't be used here.
	/** Pointer to the slot machine used to produce this result */
	UPROPERTY() TObjectPtr< USlotMachine > SlotMachine;

	/** Calculates results of lines */
	void CalcLineResults();

	/** Get element at the specified row and column */
	TSubclassOf< USlotMachineElement > GetElementType( int ColumnIndex, int RowIndex ) const { return Elements[ ColumnIndex ].Elements[ RowIndex ]; }
	
	/** Checks if a specific element is in a line */
	static bool IsElementInLine( int ElementColumnIndex, int ElementRowIndex, const TSubclassOf< USlotMachineLine >& Line );

	/** Finds all lines that contain a specific element */
	void FindLinesContainingElement( int ElementColumnIndex, int ElementRowIndex, TArray< TSubclassOf< USlotMachineLine > >& LinesContainingElement ) const;

	/** Finds the number of elements of the given type in a line */
	int FindNumberOfElementTypeInLine( const TSubclassOf< USlotMachineElement >& ElementType, const TSubclassOf< USlotMachineLine >& Line ) const;
	
public:
	void Init( USlotMachine* UsedSlotMachine );

	/** Gets all won lines */
	UFUNCTION( BlueprintPure )
	TArray< TSubclassOf< USlotMachineLine > > GetWonLines() const;

	/** Returns if the element with the specified indices is in a winning line */
	UFUNCTION( BlueprintCallable )
	bool IsElementWinning( int ElementColumnIndex, int ElementRowIndex ) const;

	/** Gets the overall payout of the result */
	UFUNCTION( BlueprintPure )
	float GetPayout() const { return Payout; }
};
