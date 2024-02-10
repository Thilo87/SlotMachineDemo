// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachine/SlotMachine.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "SlotMachineWidget.generated.h"

/**
 * Graphical representation of a slot machine object
 */
UCLASS( Category = "Slot Machine Widget" )
class SLOTMACHINEDEMO_API USlotMachineWidget : public UUserWidget
{
	GENERATED_BODY()

	/** Pointer to the object that has been created from the slot machine type */
	UPROPERTY()
	TObjectPtr< USlotMachine > SlotMachine;

public:
	virtual void NativeConstruct() override;

	/** Type of the used slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Slot Machine Widget|Properties" )
	TSubclassOf< USlotMachine > SlotMachineType;

	/** Created object of the slot machine type */
	UFUNCTION( BlueprintPure, Category = "Slot Machine Widget" )
	const USlotMachine* GetSlotMachine() const { return SlotMachine; }

	/** Called when the bet size has been changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Slot Machine Widget" )
	void OnBetSizeChanged( float NewBetSize );

	/** Called when the number of selected lines has been changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Slot Machine Widget" )
	void OnNumSelectedLinesChanged( int NewNumSelectedLines );

	/** Called when the bank balance has been changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Slot Machine Widget" )
	void OnBankBalanceChanged( float NewBalance );
};
