#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	AABFountain();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated = OnRep_ServerRotationYaw)
	float ServerRotationYaw;

	UPROPERTY(ReplicatedUsing = OnRep_ServerLightColor)
	FLinearColor ServerLightColor;

	UFUNCTION()
	void OnRep_ServerRotationYaw();

	UFUNCTION()
	void OnRep_ServerLightColor();

	float RotationRate = 30.f;
	float ClientTimeSinceUpdate = 0.f;
	float ClientTimeBetweenLastUpdate = 0.f;

	//float BigDataElement = 0.f;
};
