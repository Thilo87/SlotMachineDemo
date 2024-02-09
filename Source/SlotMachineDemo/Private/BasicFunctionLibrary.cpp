// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicFunctionLibrary.h"

#include "Kismet/KismetTextLibrary.h"

void UBasicFunctionLibrary::DollarToText(float Dollar, FText& Text, bool bSwitchCentDollar)
{
	Text = FText();
	
	FString TextAsString;
	
	FString Sign = TEXT( "$" );
	if ( FMath::Abs( Dollar ) < 1.f && bSwitchCentDollar )
	{
		Sign = TEXT( "¢" );
		TextAsString = UKismetTextLibrary::Conv_FloatToText(
			Dollar * 100.f,
			HalfFromZero,
			false,
			true,
			1,
			324,
			0,
			0
			).ToString();
	}
	else
	{
		TextAsString = UKismetTextLibrary::Conv_FloatToText(
			Dollar,
			HalfFromZero,
			false,
			true,
			1,
			324,
			2,
			2
			).ToString();
	}
		

	TextAsString += " " + Sign;
	Text = FText::FromString( TextAsString );
}
