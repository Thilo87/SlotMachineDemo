// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SlotMachineElement.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineElement : public UObject
{
	GENERATED_BODY()

public:
	/** Payout for the element if hitting n elements */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TMap< int, float > Payout;
	
	/** Material used for the element */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TObjectPtr< UMaterialInterface > Material;
};
