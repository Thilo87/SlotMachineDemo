// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Bank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBankBalanceChanged, float, NewBalance );

/**
 * A bank for storing money.
 */
UCLASS( Blueprintable, Category = "Bank" )
class SLOTMACHINEDEMO_API UBank : public UObject
{
	GENERATED_BODY()

	/** Current balance */
	float Balance = 0.f;

public:
	void Init();

	/** Called when the balance has been changed */
	UPROPERTY( BlueprintAssignable, Category = "Bank" )
	FBankBalanceChanged OnBankBalanceChanged;

	/** Balance with a newly created bank */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Bank|Balance" )
	float StartingBalance = 100.f;

	/** Gets the current balance */
	UFUNCTION( BlueprintPure, Category = "Bank|Balance" )
	float GetBalance() const;

	/** Adds money to the balance (or subtracts it). Returns false if the balance is not high enough. */
	UFUNCTION( BlueprintPure, Category = "Bank|Balance" )
	bool AddToBalance( float Amount );
};
