// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SlotMachineElement.generated.h"

/**
 * Element in a slot machine. It's one of the symbols that when you hit a few of them with a line, you get a payout.
 */
UCLASS( Blueprintable )
class SLOTMACHINEDEMO_API USlotMachineElement : public UObject
{
	GENERATED_BODY()

public:
	/** Payout for the element if hitting n elements with a line */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TMap< int, float > Payout;
};
