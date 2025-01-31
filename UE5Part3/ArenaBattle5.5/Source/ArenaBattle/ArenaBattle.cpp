#include "ArenaBattle.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogABNetwork);
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ArenaBattle, "ArenaBattle" );

// int32 GetPIEInstanceID()
// {
// 	if (GEngine && GEngine->GetWorldContexts().Num() > 0)
// 	{
// 		const FWorldContext& Context = GEngine->GetWorldContexts()[0];
// 		return Context.PIEInstance;
// 	}
// 	return -1; // PIE가 아닌 경우
// }