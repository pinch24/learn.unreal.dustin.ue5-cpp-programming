#pragma once

#include "CoreMinimal.h"

#define LOG_NETMODEINFO \
    ((GetNetMode() == NM_Client) ? TEXT("CLIENT_n") : \
    ((GetNetMode() == NM_Standalone) ? TEXT("STANDALONE") : \
    ((GetNetMode() == NM_ListenServer) ? TEXT("LISTEN_SERVER") : TEXT("DEDICATED_SERVER"))))
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define AB_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s] %s %s"), LOG_NETMODEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);