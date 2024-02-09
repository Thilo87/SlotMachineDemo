// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachine.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "SlotMachineColumnWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineColumnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FSlotMachineColumn Column;
};
