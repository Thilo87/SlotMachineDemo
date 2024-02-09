// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "Bank.h"

void UBank::Init()
{
	AddToBalance( StartingBalance );
}

float UBank::GetBalance() const
{
	return Balance;
}

bool UBank::AddToBalance(float Amount)
{
	if ( Balance + Amount < 0.f )
		return false;

	Balance += Amount;

	if ( Amount != 0.f )
		OnBankBalanceChanged.Broadcast( Balance );
	
	return true;
}
