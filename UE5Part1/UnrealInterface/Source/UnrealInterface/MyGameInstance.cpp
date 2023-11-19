// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
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

	UE_LOG(LogTemp, Warning, TEXT("================================================================"));
	
	TArray<UPerson *> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };
	for (const auto Person : Persons) {
		UE_LOG(LogTemp, Warning, TEXT("Member Name: %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("================================================================"));

	for (const auto Person: Persons) {
		ILessonInterface* LessionInterface = Cast<ILessonInterface>(Person);
		if (LessionInterface) {
			UE_LOG(LogTemp, Warning, TEXT("%s can participate in the class."), *Person->GetName());
			LessionInterface->DoLesson();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("%s is not allowed to participate in the class."), *Person->GetName());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("================================================================"));
}
