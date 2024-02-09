// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BasicFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SLOTMACHINEDEMO_API UBasicFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*
	 *
	 * Displaying text
	 *
	 */

	/** Converts dollar to text, e.g. 1.2 to "1.20 $" and 0.5 to "0.50 $". If bSwitchCentDollar it would instead convert 0.5 to "50 ¢" */
	UFUNCTION( BlueprintPure )
	static void DollarToText( float Dollar, FText& Text, bool bSwitchCentDollar = true );
};
