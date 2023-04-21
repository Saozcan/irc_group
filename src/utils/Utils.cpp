//
// Created by ebudak on 3/13/23.
//

#include "Utils.hpp"

static std::vector<std::string> Utils::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    if (end > str.length()) {
        tokens.push_back(str.substr(start, str.length()));
        return tokens;
    }
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    if (start != str.length()) {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}