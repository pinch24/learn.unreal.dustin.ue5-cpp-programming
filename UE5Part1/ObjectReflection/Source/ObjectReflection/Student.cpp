// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Year = 1;
	Id = 1;
	Name = TEXT("Student");
}

void UStudent::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Warning, TEXT("%drd grade, %drd class %s is taking a class."), Year, Id, *Name);
}
