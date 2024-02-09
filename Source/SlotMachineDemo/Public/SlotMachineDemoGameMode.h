// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bank.h"
#include "GameFramework/GameMode.h"
#include "UObject/Object.h"
#include "SlotMachineDemoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API ASlotMachineDemoGameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr< UBank > Bank;

public:
	virtual void BeginPlay() override;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< UBank > BankType;

	UFUNCTION( BlueprintPure )
	UBank* GetBank() const { return Bank; }
};
