// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("Person");
	Year = 1;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Warning, TEXT("%s attend the class."), *Name);
}

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name = InName;
}
