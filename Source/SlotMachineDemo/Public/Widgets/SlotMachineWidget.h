// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotMachine.h"
#include "SlotMachineElementWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "SlotMachineWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API USlotMachineWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr< USlotMachine > SlotMachine;

public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< USlotMachine > SlotMachineType;

	UFUNCTION( BlueprintPure )
	const USlotMachine* GetSlotMachine() const { return SlotMachine; }

	UFUNCTION( BlueprintImplementableEvent )
	void OnBetSizeChanged( float NewBetSize );

	UFUNCTION( BlueprintImplementableEvent )
	void OnNumSelectedLinesChanged( int NewNumSelectedLines );

	virtual void NativeConstruct() override;
};
