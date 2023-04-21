#pragma once

#include "iostream"
#include "vector"
#include "map"

#include "../server/Server.hpp"

class Server;

class Utility {
public:
    static bool checkAndParse(Server &server, pollfd &poll, char* str);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    static const std::string toUpper(const std::string &str);
    static std::string strTrim(std::string str);
    static std::string trimExceptAlphabet(std::string str);
    static ssize_t sendToClient(int fd, const std::string &str);
};


