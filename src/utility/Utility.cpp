

#include "Utility.hpp"
//Statics
bool Utility::checkAndParse(Server &server, pollfd &poll, char* str) {
    std::string buffer(str);
    std::vector<std::string> splitSpace = Utility::split(buffer, " ");
    if (Utility::toUpper(splitSpace[0]) == "PASS")
        return true;

    return false;
}

std::vector<std::string> Utility::split(const std::string& str, const std::string& delimiter) {
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

const std::string Utility::toUpper(const std::string &str) {
    size_t i = 0;
    std::string returnStr(str);
    while (i < str.size()) {
        returnStr[i] = toupper(returnStr[i]);
        i++;
    }
    return returnStr;
}
