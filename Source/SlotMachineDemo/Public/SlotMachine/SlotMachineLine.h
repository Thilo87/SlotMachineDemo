// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SlotMachineLine.generated.h"

/**
 * A line of a slot machine. The row indices are the indices of the rows in the columns. This is where the line goes through.
 */
UCLASS( Blueprintable )
class SLOTMACHINEDEMO_API USlotMachineLine : public UObject
{
	GENERATED_BODY()

public:
	/** Row indices of the line */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< int > RowIndices;
};
