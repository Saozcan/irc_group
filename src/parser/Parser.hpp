//
// Created by ebudak on 3/11/23.
//

#ifndef PARSER_HPP
#define PARSER_HPP


#include <iostream>
#include <vector>
#include "../utils/Utils.hpp"

#include "ParserMode.hpp"

class ParserMode;
class Parser {
public:
    std::vector<std::string> v1;
    std::vector<std::string> v2;

    std::vector<std::string> parse_irc_message(std::string msg);
    void commandParser(std::string irc_msg, ParserMode &p);
};


#endif //IRC_GROUP_PARSER_HPP
