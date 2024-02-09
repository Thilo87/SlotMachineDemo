// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SlotMachineLine.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineLine : public UObject
{
	GENERATED_BODY()

public:
	/** Row indices of the line */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray< int > RowIndices;
};
