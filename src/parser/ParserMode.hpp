//
// Created by ebudak on 3/12/23.
//

#ifndef PARSERMODE_HPP
#define PARSERMODE_HPP

#include <iostream>
#include <vector>

class ParserMode {
public:
    std::vector<std::pair<std::string, char>> parse_mode_flags(std::string mode);
};


#endif //IRC_GROUP_PARSERMODE_HPP
