// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Card.h"
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
	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		ECardType CardType = OwnCard->GetCardType();
		
		if (const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType")))
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Warning, TEXT("%s's Card Type: %s"), *Person->GetName(), *CardMetaData);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("================================================================"));
}
