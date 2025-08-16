#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABCharacterItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UABCharacterItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLE_API IABCharacterItemInterface
{
	GENERATED_BODY()

public:
	virtual void TakeItem(class UABItemData* InItemData) = 0;
};
