#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "user32.lib")

#include <windows.h>
#include "Hooking.Patterns\Hooking.Patterns.h"
#include "IniReader\IniReader.h"

void Init() {
    auto pattern = hook::pattern("C3 64 2A 3A E3 8B F6 3A 07 42 B2 38");

    if (pattern.empty()) {
        MessageBox(NULL, TEXT("Could not find the coefficients pattern! No changes were made."), TEXT("MSFS2020.ARPC"), MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
        return;
    }

    CIniReader iniReader("");

    const auto pCoefficients = pattern.get_first<float>();
    const float fCoefficients[] = {pCoefficients[0], pCoefficients[1], pCoefficients[2]};
    const float fNewCoefficients[] = {
        iniReader.ReadFloat("COEFFICIENTS", "RED", 0.002723f),
        iniReader.ReadFloat("COEFFICIENTS", "GREEN", 0.001831f),
        iniReader.ReadFloat("COEFFICIENTS", "BLUE", -0.000083096f),
    };

    std::copy(std::begin(fNewCoefficients), std::end(fNewCoefficients), pCoefficients);

    const auto bToggleEnabled = iniReader.ReadBoolean("TOGGLE", "ENABLED", FALSE);

    if (bToggleEnabled) {
        const auto key = iniReader.ReadInteger("TOGGLE", "KEY_CODE", 0x2D);
        const auto modifier = MOD_NOREPEAT
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_ALT", FALSE) * MOD_ALT)
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_CTRL", FALSE) * MOD_CONTROL)
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_SHIFT", FALSE) * MOD_SHIFT);

        RegisterHotKey(NULL, 1, modifier, key);

        bool bPatchEnabled = true;
        MSG msg = {0};
        while (GetMessage(&msg, NULL, 0, 0) != 0)
        {
            if (msg.message != WM_HOTKEY)
                continue;

            const auto _fCoefficients = bPatchEnabled ? &fCoefficients : &fNewCoefficients;
            std::copy(std::begin(*_fCoefficients), std::end(*_fCoefficients), pCoefficients);
            bPatchEnabled = !bPatchEnabled;
        }
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Init, NULL, NULL, NULL));
    }

    return TRUE;
}
