#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

inline std::unordered_map<std::string, std::string> parseConfFile(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r") + 1);

        if (line.empty() || line[0] == '#') continue; // skip empty lines and comments

        size_t pos = line.find('=');
        if (pos == std::string::npos) continue; // skip lines without =

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // trim whitespace from key and value
        key.erase(0, key.find_first_not_of(" \t\n\r"));
        key.erase(key.find_last_not_of(" \t\n\r") + 1);
        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);

        config[key] = value;
    }

    return config;
}

