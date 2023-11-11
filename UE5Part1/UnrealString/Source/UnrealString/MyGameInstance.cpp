// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();
	
	static const TCHAR LogCharArray[] = TEXT("Hello, Unreal.");
	UE_LOG(LogTemp, Log, LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR * LogCharPtr = *LogCharString;
	TCHAR * LogCharDataPtr = LogCharString.GetCharArray().GetData();

	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase)) {
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("Find Test: %s"), *EndString);
	}

	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right)) {
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s and %s"), *Left, *Right);
	}

	int32 IntValue = 32;
	float FloatValue = 3.141592;
	FString FloatIntString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int: %s, Float: %s"), *IntString, *FloatString);

	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	FString FloatIntFromString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntFromString);
	
	FName Key1(TEXT("PELVIS"));
	FName Key2(TEXT("pelvis"));
	UE_LOG(LogTemp, Log, TEXT("FName Compare Result: %s"), Key1 == Key2 ? TEXT("Same") : TEXT("Different"));

	for (int i = 0; i < 10000; i ++) {
		FName SearchInNamePool = FName(TEXT("pelvis"));
		const static FName StaticOnlyOnce(TEXT("pelvis"));
	}
}