// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Year = 1;
	Id = 1;
	Name = TEXT("Teacher");
}

void UTeacher::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Warning, TEXT("%d years old %s teaches the class."), Year + Id, *Name);
}
