// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineElement.h"
#include "SlotMachineLine.h"
#include "UObject/Object.h"
#include "SlotMachineResult.generated.h"

USTRUCT( BlueprintType )
struct FSlotMachineElementResult
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachineElement > ElementType;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TArray< TSubclassOf< USlotMachineLine > > Lines;
};

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

USTRUCT( BlueprintType )
struct FSlotMachineColumnResult
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TArray< FSlotMachineElementResult > Elements;
};

/**
 * 
 */
UCLASS( BlueprintType )
class SLOTMACHINEDEMO_API USlotMachineResult : public UObject
{
	GENERATED_BODY()

	TArray< FSlotMachineLineResult > LineResults;
	float Payout = 0.f;

	TArray< FSlotMachineColumnResult > Elements;
	
public:
	UFUNCTION( BlueprintPure )
	TArray< TSubclassOf< USlotMachineLine > > GetWonLines() const;

	UFUNCTION( BlueprintPure )
	float GetPayout() const { return Payout; }

	friend class USlotMachine;
};
