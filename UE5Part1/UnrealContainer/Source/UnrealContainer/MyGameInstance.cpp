// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1; ix <= ArrayNum; ix++)
	{
		Int32Array.Add(ix);
	}

	Int32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	Int32Array += { 2, 4, 6, 8, 10 };

	TArray<int32> Int32ArrayCompare;
	const int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	const int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);
}
