// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "HiddenCheats.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        DisableThreadLibraryCalls(hModule);
        HiddenCheats::Run();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

