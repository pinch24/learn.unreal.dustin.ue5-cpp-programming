#include "Player/ABPlayerController.h"
#include "ArenaBattle.h"
#include "UI/ABHUDWidget.h"

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C'"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AABPlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void AABPlayerController::GameClear()
{
	K2_OnGameClear();
}

void AABPlayerController::GameOver()
{
	K2_OnGameOver();
}

void AABPlayerController::PostInitializeComponents()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostInitializeComponents();
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABPlayerController::PostNetInit()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
		{
			AB_LOG(LogABNetwork, Log, TEXT("Server Connections is %s"), *NetDriver->ServerConnection->GetName());
		}
		else
		{
			AB_LOG(LogABNetwork, Error, TEXT("Server Connections is NULL"));
		}
	}
	else
	{
		AB_LOG(LogABNetwork, Error, TEXT("%s"), TEXT("NetDriver is NULL."));
	}
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABPlayerController::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::BeginPlay();
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));

	// FInputModeUIOnly InputMode;
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	if (IsLocalPlayerController())
	{
		ABHUDWidget = CreateWidget<UABHUDWidget>(this, ABHUDWidgetClass);
		if (ABHUDWidget)
		{
			ABHUDWidget->AddToViewport();
		}
	}
}

void AABPlayerController::OnPossess(APawn* InPawn)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::OnPossess(InPawn);

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
