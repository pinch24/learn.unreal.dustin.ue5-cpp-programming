#include "CharacterStat/ABCharacterStatComponent.h"

#include "ArenaBattle.h"
#include "GameData/ABGameSingleton.h"
#include "Net/UnrealNetwork.h"

UABCharacterStatComponent::UABCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.f;

	bWantsInitializeComponent = true;

	SetIsReplicated(true);
}

void UABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UABCharacterStatComponent::BeginPlay()
{
	AB_SUBLOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();
}

void UABCharacterStatComponent::ReadyForReplication()
{
	AB_SUBLOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::ReadyForReplication();
}

void UABCharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UABCharacterStatComponent, CurrentHp);
}

void UABCharacterStatComponent::OnRep_CurrentHp()
{
	AB_SUBLOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	OnHpChanged.Broadcast(CurrentHp);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
}

void UABCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UABGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(UABGameSingleton::Get().GetCharacterStat(CurrentLevel));
	check(BaseStat.MaxHp > 0.f);
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.f, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.f, BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}
