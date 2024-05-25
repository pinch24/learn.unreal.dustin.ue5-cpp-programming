// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Order = -1;
	Name = TEXT("Charlie");
}

void UStudent::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);

	Ar << Order;
	Ar << Name;
}
