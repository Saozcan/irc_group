

#include "Utility.hpp"
//Statics
bool Utility::checkAndParse(Server &server, pollfd &poll, char* str) {
    std::string buffer(str);
    std::vector<std::string> splitSpace = Utility::split(buffer, " ");
    if (Utility::toUpper(splitSpace[0]) == "PASS")
        return true;

    return false;
}

unsigned int passDelimiter(const std::string &str, const std::string& delimiter) {
    unsigned int i = 0;
    while (str[i] != std::string::npos) {
        if (str[i] == delimiter[0])
            i++;
        else
            break;
    }
    return i;
}

std::vector<std::string> Utility::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        if (end > start) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + delimiter.length();
        end = str.find(delimiter, start);
        while (end == start) {
            start += delimiter.length();
            end = str.find(delimiter, start);
        }
    }
    if (start < str.length()) {
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

std::string Utility::strTrim(std::string str){

    size_t found1 = str.find('\r');
    size_t found2 = str.find('\n');
    size_t found3 = str.find('#') !=  std::string::npos ?  str.find('#'): str.find('&');
    if(found3 != std::string::npos)
        str = str.substr(found3 + 1, str.length() -1);
    if(found1 != std::string::npos)
        str = str.substr(0, found1);
    if(found2 != std::string::npos)
        str = str.substr(0,found2);
    return str;
}

std::string Utility::trimExceptAlphabet(std::string str) {
    std::string::reverse_iterator it = str.rbegin();
    for (; it != str.rend(); it++) {
        if ((*it) == '\r' || (*it) == '\n')
            str.pop_back();
        else
            break;
    }
    return str;
}


