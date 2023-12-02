// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

UINTERFACE()
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALCOMPOSITION_API ILessonInterface
{
	GENERATED_BODY()
	
public:
	virtual void DoLesson();
};
