//
// Created by ebudak on 3/12/23.
//

#include "ParserMode.hpp"
std::vector<std::pair<std::string, char>> ParserMode::parse_mode_flags(std::string mode) {
    std::vector<std::pair<std::string, char>> flags;
    size_t pos = 0;
    while (pos < mode.length()) {
        if (mode[pos] == '+' || mode[pos] == '-') {
            char op = mode[pos];
            pos++;
            while (pos < mode.length() && mode[pos] != '+' && mode[pos] != '-') {
                if (mode[pos] == 'o') {
                    flags.emplace_back(mode.substr(pos + 1, 1), op);
                }
                pos++;
            }
        } else {
            pos++;
        }
    }
    return flags;
}
