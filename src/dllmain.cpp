#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Hooking.Patterns\Hooking.Patterns.h"

void Init() {
    auto pattern = hook::pattern("C3 64 2A 3A E3 8B F6 3A 07 42 B2 38");

    if (pattern.empty()) {
        MessageBox(NULL, TEXT("Could not find the coefficients pattern! No changes were made."), TEXT("MSFS.ARPC"), MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
        return;
    }

    *reinterpret_cast<float*>(pattern.get_first()) = 0.0027234f;
    *reinterpret_cast<float*>(pattern.get_first(4)) = 0.001831f;
    *reinterpret_cast<float*>(pattern.get_first(8)) = -0.000083096f;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Init, NULL, NULL, NULL));
    }

    return TRUE;
}
