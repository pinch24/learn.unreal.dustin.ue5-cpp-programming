// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"


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

	UStudent * Student = NewObject<UStudent>();
	Student->SetName(TEXT("Mason Kei"));
	UE_LOG(LogTemp, Warning, TEXT("New Student Name: %s"), *Student->GetName());

	UTeacher * Teacher = NewObject<UTeacher>();
	FString CurrentTeacherName;
	const FString NewTeacherName(TEXT("Timothy D. Sweeney"));
	if (const FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"))) {
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Warning, TEXT("Currnet Teacher Name: %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Warning, TEXT("New Teacher Name: %s"), *Teacher->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("================================"));

	Student->DoLesson();
	
	if (UFunction * DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"))) {
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("================================"));
}
