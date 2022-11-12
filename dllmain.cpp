#include "include/initialize.hpp"
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwCallReason, LPVOID lpReserved)
{
    g_hModule = hModule;
    switch (dwCallReason) {
        case (DLL_PROCESS_ATTACH): {
            DisableThreadLibraryCalls(hModule);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, g_hModule, NULL, NULL);
            break;
        }
        case (DLL_PROCESS_DETACH): {
            g_Killswitch = TRUE;
            break;
        }
    }
    return TRUE;
}