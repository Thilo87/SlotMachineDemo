// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

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

	/** Bank object containing balance */
	UPROPERTY()
	TObjectPtr< UBank > Bank;

public:
	virtual void BeginPlay() override;

	/** The bank type to create */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< UBank > BankType;

	/** Gets the currently selected bank */
	UFUNCTION( BlueprintPure )
	UBank* GetBank() const { return Bank; }
};
