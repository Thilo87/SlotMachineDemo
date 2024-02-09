// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachineColumnWidget.h"
#include "SlotMachineWidget.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "SlotMachineColumnsDisplayWidget.generated.h"

/**
 * A widget for displaying multiple columns of a slot machine
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineColumnsDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Type of the slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachine > SlotMachineType;

	/** Type of the used graphical representation of a slot machine column */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachineColumnWidget > SlotMachineColumnWidgetType;
};
