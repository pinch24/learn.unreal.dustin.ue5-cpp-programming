#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/GameModeBase.h"	// 빌드 오류 때문에 추가
#include "ABGameInterface.generated.h"

UINTERFACE(MinimalAPI)
class UABGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLE_API IABGameInterface
{
	GENERATED_BODY()

public:
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) = 0;
	virtual void OnPlayerDead() = 0;
	virtual bool IsGameCleared() = 0;
};
