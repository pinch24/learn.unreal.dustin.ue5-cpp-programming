#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterStat.h"
#include "ABGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameSingleton : public UObject
{
	GENERATED_BODY()

private:
	TArray<FABCharacterStat> CharacterStatTable;
	
public:
	UABGameSingleton();
	static UABGameSingleton& Get();

	FORCEINLINE FABCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FABCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;
};
