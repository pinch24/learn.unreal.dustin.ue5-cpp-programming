// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("Timothy");
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Warning, TEXT("%s teaches."), *Name);
}
