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
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineWidget : public UUserWidget
{
	GENERATED_BODY()

	/** Pointer to the object that has been created from the slot machine type */
	UPROPERTY()
	TObjectPtr< USlotMachine > SlotMachine;

public:
	virtual void NativeConstruct() override;

	/** Type of the used slot machine */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachine > SlotMachineType;

	/** Created object of the slot machine type */
	UFUNCTION( BlueprintPure )
	const USlotMachine* GetSlotMachine() const { return SlotMachine; }

	/** Called when the bet size has been changed */
	UFUNCTION( BlueprintImplementableEvent )
	void OnBetSizeChanged( float NewBetSize );

	/** Called when the number of selected lines has been changed */
	UFUNCTION( BlueprintImplementableEvent )
	void OnNumSelectedLinesChanged( int NewNumSelectedLines );

	/** Called when the bank balance has been changed */
	UFUNCTION( BlueprintImplementableEvent )
	void OnBankBalanceChanged( float NewBalance );
};
