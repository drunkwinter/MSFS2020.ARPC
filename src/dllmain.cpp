#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "user32.lib")

#include <windows.h>
#include "Hooking.Patterns\Hooking.Patterns.h"
#include "IniReader\IniReader.h"

std::atomic<bool> hotkey_pressed(false);
std::atomic<bool> ini_file_changed(false);

inline void listen_for_hotkey(int key, int modifiers) {
    if (RegisterHotKey(nullptr, 1, modifiers, key)) {
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            if (msg.message == WM_HOTKEY) {
                hotkey_pressed = true;
            }
        }
    }
}

inline void listen_for_filechange(const char* ini_file_path) {
    auto handle = FindFirstChangeNotificationA(".", FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

    if (handle == INVALID_HANDLE_VALUE) {
        return;
    }

    auto last_modified_time = std::filesystem::last_write_time(ini_file_path);

    while (WaitForSingleObject(handle, INFINITE) == WAIT_OBJECT_0) {
        const auto current_modified_time = std::filesystem::last_write_time(ini_file_path);

        if (current_modified_time != last_modified_time) {
            last_modified_time = current_modified_time;

            ini_file_changed = true;
        }

        FindNextChangeNotification(handle);
    }
}

inline void show_warning(const char* message) {
    MessageBoxA(nullptr, message, "MSFS2020.ARPC", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
}

class Config {
public:
    Config() {
        update();
    }

    inline static bool live_editing_enabled;
    inline static bool toggle_enabled;
    inline static int toggle_key;
    inline static int toggle_modifiers;
    inline static float coefficients[3];

    inline static constexpr const char* ini_path = "./MSFS2020.ARPC.ini";

    static void update() {
        CIniReader iniReader("");

        live_editing_enabled = iniReader.ReadBoolean("COEFFICIENTS", "LIVE_EDITING_ENABLED", FALSE);

        coefficients[0] = iniReader.ReadFloat("COEFFICIENTS", "RED", 0.002723f);
        coefficients[1] = iniReader.ReadFloat("COEFFICIENTS", "GREEN", 0.001831f);
        coefficients[2] = iniReader.ReadFloat("COEFFICIENTS", "BLUE", -0.000083096f);

        toggle_enabled = iniReader.ReadBoolean("TOGGLE", "ENABLED", FALSE);
        toggle_key = iniReader.ReadInteger("TOGGLE", "KEY_CODE", 0x2D);
        toggle_modifiers = MOD_NOREPEAT
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_ALT", FALSE) * MOD_ALT)
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_CTRL", FALSE) * MOD_CONTROL)
            | (iniReader.ReadBoolean("TOGGLE", "HOLD_SHIFT", FALSE) * MOD_SHIFT);
    }
};

void init() {
    auto pattern = hook::pattern("C3 64 2A 3A E3 8B F6 3A 07 42 B2 38");

    if (pattern.empty()) {
        show_warning("Could not find the coefficients pattern! No changes were made.");
        return;
    }

    const auto coefficients = pattern.get_first<float>();
    const float default_coefficients[] = {coefficients[0], coefficients[1], coefficients[2]};

    Config config{};

    std::copy(std::begin(Config::coefficients), std::end(Config::coefficients), coefficients);

    if (Config::live_editing_enabled) {
        std::thread file_thread(listen_for_filechange, Config::ini_path);
        file_thread.detach();
    }

    if (Config::toggle_enabled) {
        std::thread input_thread(listen_for_hotkey, Config::toggle_key, Config::toggle_modifiers);
        input_thread.detach();
    }

    bool patch_enabled = true;

    while (true) {
        if (hotkey_pressed) {
            hotkey_pressed = false;

            patch_enabled = !patch_enabled;

            if (patch_enabled) {
                std::copy(std::begin(Config::coefficients), std::end(Config::coefficients), coefficients);
            } else {
                std::copy(std::begin(default_coefficients), std::end(default_coefficients), coefficients);
            }
        }

        if (ini_file_changed) {
            ini_file_changed = false;

            Config::update();

            if (patch_enabled) {
                std::copy(std::begin(Config::coefficients), std::end(Config::coefficients), coefficients);
            }
        }
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        std::thread main_thread(init);
        main_thread.detach();
    }

    return TRUE;
}
