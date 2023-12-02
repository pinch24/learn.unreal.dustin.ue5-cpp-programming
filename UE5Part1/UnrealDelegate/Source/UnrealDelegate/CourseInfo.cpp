// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("Existing Course Info");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;

	UE_LOG(LogTemp, Warning, TEXT("[CourseInfo] Send notification when course info changes."));
	OnChanged.Broadcast(InSchoolName, Contents);
}
