#pragma once

#include "CoreMinimal.h"
#include "ABUserWidget.h"
#include "ABHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHpBarWidget : public UABUserWidget
{
	GENERATED_BODY()

public:
	UABHpBarWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
