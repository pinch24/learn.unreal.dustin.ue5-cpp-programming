// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Basic School");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("================================"));
	UClass * ClassRuntime = GetClass();
	UClass * ClassCompile = UMyGameInstance::StaticClass();
	// check(ClassRuntime != ClassCompile);
	// ensure(ClassRuntime != ClassCompile);
	ensureMsgf(ClassRuntime != ClassCompile, TEXT("Ensure Message!"));
	UE_LOG(LogTemp, Warning, TEXT("Class Name: %s"), *ClassRuntime->GetName());

	SchoolName = TEXT("Epic Game Arcademy");
	UE_LOG(LogTemp, Warning, TEXT("School Name: %s"), *SchoolName);
	UE_LOG(LogTemp, Warning, TEXT("School Name Basic: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);
	
	UE_LOG(LogTemp, Warning, TEXT("================================"));
}
