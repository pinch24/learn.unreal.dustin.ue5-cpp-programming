// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "JsonObjectConverter.h"
#include "Student.h"
#include "UObject/PackageRelocation.h"
#include "UObject/SavePackage.h"

const FString UMyGameInstance::PackageName = TEXT("/Game/Student");
const FString UMyGameInstance::AssetName = TEXT("TopStudent");

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Name: %s, Seq: %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(*TopSoftObjectPath);
	if (UASSET_TopStudent.Succeeded())
	{
		PrintStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(16, TEXT("Bravo"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Warning, TEXT("Saved File Directory: %s"), *SavedDir);

	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
		UE_LOG(LogTemp, Warning, TEXT("Saved File Path: %s"), *RawDataAbsolutePath);
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Warning, TEXT("Edited File Path: %s"), *RawDataAbsolutePath);

		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (RawFileWriterAr != nullptr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (RawFileReaderAr != nullptr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Warning, TEXT("[RawData] Name: %s, Seq: %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("Delta"));
	StudentSrc->SetOrder(59);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);
		
		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}
		
		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}
		
		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDest, TEXT("ObjectData"));
	}

	{
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);

		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
		}

		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);
		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	Handle = StremableManager.RequestAsyncLoad(TopSoftObjectPath, [&]()
	{
		if (Handle.IsValid() && Handle->HasLoadCompleted())
		{
			UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
			if (TopStudent)
			{
				PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));
				Handle->ReleaseHandle();
				Handle.Reset();
			}
		}
	});
}

void UMyGameInstance::SaveStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}
		
	StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	UStudent* TopStudent = NewObject<UStudent>(StudentPackage, UStudent::StaticClass(), *AssetName, ObjectFlag);
	TopStudent->SetName(TEXT("Echo"));
	TopStudent->SetOrder(36);

	const int32 NumOfSubs = 10;
	for (int32 ix = 1; ix <= NumOfSubs; ++ix)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"), ix);
		UStudent* SubStudent = NewObject<UStudent>(TopStudent, UStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("Student%d"), ix));
		SubStudent->SetOrder(ix);
	}

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Warning, TEXT("Package was successfully saved."));
	}
}

void UMyGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Package not found."));
		return;
	}

	StudentPackage->FullyLoad();

	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	PrintStudentInfo(TopStudent, TEXT("FindObject Asset"));
}

void UMyGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);
	PrintStudentInfo(TopStudent, TEXT("LoadObject Asset"));
}
