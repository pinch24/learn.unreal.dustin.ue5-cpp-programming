// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "CopyTextureShaders.h"
#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("ABCD");
	TCHAR MiddleChar[] = TEXT("abcd");
	TCHAR LastChar[] = TEXT("1234");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();
}

void UMyGameInstance::Init()
{
	Super::Init();

	// TArray
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

	// TSet
	TSet<int32> Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ix++)
	{
		Int32Set.Add(ix);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	const int32 StudentNum = 300;
	for (int32 ix = 1; ix < StudentNum; ix++)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), ix));
	}
	
	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentsData, AllStudentsNames, [](const FStudentData& Val)
	{
		return Val.Name;
	});
	UE_LOG(LogTemp, Warning, TEXT("All Stududents Name Count: %d"), AllStudentsNames.Num());
	
	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentsData, AllUniqueNames, [](const FStudentData& Val)
	{  
		return Val.Name;
	});
	UE_LOG(LogTemp, Warning, TEXT("Unduplicated Stududents Name Count: %d"), AllUniqueNames.Num());

	Algo::Transform(StudentsData, StudentsMap, [](const FStudentData& Val)
	{
		return TPair<int32, FString>(Val.Order, Val.Name);
	});
	UE_LOG(LogTemp, Warning, TEXT("Ordered Stududents Map Count: %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;
	Algo::Transform(StudentsData, StudentsMapByUniqueName, [](const FStudentData& Val)
	{
		return TPair<FString, int32>(Val.Name, Val.Order);
	});
	UE_LOG(LogTemp, Warning, TEXT("Named Stududents Map Count: %d"), StudentsMapByUniqueName.Num());
	
	TMultiMap<FString, int32> StudentsMapByName;
	Algo::Transform(StudentsData, StudentsMapByName, [](const FStudentData& Val)
	{
		return TPair<FString, int32>(Val.Name, Val.Order);
	});
	UE_LOG(LogTemp, Warning, TEXT("Named Stududents Multi Map Count: %d"), StudentsMapByName.Num());

	const FString TargetName(TEXT("Ab1"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);
	UE_LOG(LogTemp, Warning, TEXT("Named %s Map Count: %d"), *TargetName, AllOrders.Num());

	TSet<FStudentData> StudentsSet;
	for (int32 ix = 1; ix <= StudentNum; ix++)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
	}
}
