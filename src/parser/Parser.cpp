//
// Created by ebudak on 3/11/23.
//

#include "Parser.hpp"

Parser::Parser(){

}

std::vector<std::string> Parser::parse_irc_message(std::string msg) {
    std::vector<std::string> components;
    int start_pos = 0;
    int end_pos = msg.find(" ");
    if(msg && msg[0] == ':') //TODO: Burası parse edilecek : Wiz Links...
        end_pos++;

    components  = Utils::split(msg, " ");

//    if (components.size() >= 2) {
//
//    }
    return components;
}

void Parser::commandParser(){

}
