// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Bank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBankBalanceChanged, float, NewBalance );

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API UBank : public UObject
{
	GENERATED_BODY()

	float Balance = 0.f;

public:
	void Init();

	UPROPERTY( BlueprintAssignable )
	FBankBalanceChanged OnBankBalanceChanged;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float StartingBalance = 100.f;

	UFUNCTION( BlueprintPure )
	float GetBalance() const;

	UFUNCTION( BlueprintPure )
	bool AddToBalance( float Amount );
};
