// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachine/SlotMachine.h"
#include "SlotMachineElementWidget.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "SlotMachineColumnWidget.generated.h"

/**
 * Graphical representation of a column of a slot machine
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineColumnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Type of the slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachine > SlotMachineType;

	/** Lookup for graphical representations of the slot machine elements */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TMap< TSubclassOf< USlotMachineElement >, TSubclassOf< USlotMachineElementWidget > > ElementWidgetLookup;
};
