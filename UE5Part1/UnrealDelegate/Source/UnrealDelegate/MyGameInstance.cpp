// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Card.h"
#include "CourseInfo.h"
#include "Staff.h"
#include "Student.h"
#include "Teacher.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("Basic School");
}

void UMyGameInstance::Init()
{
	Super::Init();

	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Warning, TEXT("================================================================"));
	
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("Student1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("Student2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("Student3"));

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("Changed Cousre Info"));
	
	UE_LOG(LogTemp, Warning, TEXT("================================================================"));
}
