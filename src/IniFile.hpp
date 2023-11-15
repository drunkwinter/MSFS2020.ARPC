class IniFile {
public:
    IniFile(const std::string_view ini_path) : ini_path(ini_path.data()) { }

    template <typename T>
    T get(const std::string_view section, const std::string_view key, const T default_value) const
    {
        if constexpr (std::is_same_v<T, std::string>) {
            char buffer[255];
            GetPrivateProfileStringA(section.data(), key.data(), default_value.data(), buffer, sizeof(buffer), ini_path);
            std::string string { buffer };
            if (const auto idx = string.find(" "); idx != string.npos) {
                string.erase(idx, -1);
            }
            if (const auto idx = string.find(";"); idx != string.npos) {
                string.erase(idx, -1);
            }
            return string;
        }

        if constexpr (std::is_same_v<T, bool>) {
            const auto str = get(section, key, std::to_string(default_value));
            return str == "true" || str == "1";
        }

        if constexpr (std::is_same_v<T, float>) {
            return std::stof(get(section, key, std::to_string(default_value)));
        }

        if constexpr (std::is_same_v<T, int>) {
            return GetPrivateProfileIntA(section.data(), key.data(), default_value, ini_path);
        }
    }
private:
    const char* ini_path;
};
