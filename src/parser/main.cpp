//
// Created by ebudak on 3/11/23.
//
#include "Parser.hpp"

int main(){
    Parser p;
    ParserMode pm;
    int i = 0;
    std::string str ;
    std::cin >> str;
    p.commandParser(str,pm);

//    std::vector<std::string>::iterator it = msg.begin();
//    for ( ; it < msg.end() ; it++) {
//        std::cout << *it << std::endl;
//    }

}