class IniFile {
public:
    IniFile(const std::string& ini_path) : ini_path(ini_path.c_str()) { }

    template <typename T>
    auto get(const char* section, const char* key, T default_value) const
    {
        if constexpr (std::is_same_v<T, std::string>) {
            char buffer[255];
            GetPrivateProfileStringA(section, key, default_value.c_str(), buffer, sizeof(buffer), ini_path);
            std::string str{buffer};
            if (const auto idx = str.find(" "); idx != std::string::npos) {
                str.erase(idx, -1);
            }
            if (const auto idx = str.find(";"); idx != std::string::npos) {
                str.erase(idx, -1);
            }
            return str;
        }

        if constexpr (std::is_same_v<T, const char*>) {
            const auto str = get(section, key, std::string{default_value});
            char *cstr = new char[str.size() + 1];
            strcpy(cstr, str.c_str());
            return cstr;
        }

        if constexpr (std::is_same_v<T, bool>) {
            const auto str = get(section, key, std::to_string(default_value));
            return str == "true" || str == "1";
        }

        if constexpr (std::is_same_v<T, float>) {
            return std::stof(get(section, key, std::to_string(default_value)));
        }

        if constexpr (std::is_same_v<T, int>) {
            return GetPrivateProfileIntA(section, key, default_value, ini_path);
        }
    }
private:
    const char* ini_path;
};
