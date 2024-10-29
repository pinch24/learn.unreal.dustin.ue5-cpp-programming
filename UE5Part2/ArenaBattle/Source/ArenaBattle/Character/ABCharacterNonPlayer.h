#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "ABCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS(config=ArenaBattle)
class ARENABATTLE_API AABCharacterNonPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterNonPlayer();

protected:
	virtual void PostInitializeComponents() override; 
	
	void SetDead() override;
	void NPCMeshLoadComplete();

	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;
	
	TSharedPtr<FStreamableHandle> NPCMeshHandle;
};
