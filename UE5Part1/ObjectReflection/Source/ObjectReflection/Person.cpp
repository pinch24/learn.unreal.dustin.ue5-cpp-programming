// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("Timothy D. Sweeney");
	Year = 54;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s attend the class."), *Name);
}

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name = InName;
}
