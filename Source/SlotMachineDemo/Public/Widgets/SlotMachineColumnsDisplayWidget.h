// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineColumnWidget.h"
#include "SlotMachineWidget.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "SlotMachineColumnsDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineColumnsDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachine > SlotMachineType;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachineColumnWidget > SlotMachineColumnWidgetType;
};
