//
// Created by ebudak on 3/17/23.
//
#include "Join.hpp"

Join::Join(): ACommand("JOIN"){

}

Join::~Join() {

}
/*
 *    Examples:

   JOIN #foobar                    ; join channel #foobar.

   JOIN &foo fubar                 ; join channel &foo using key "fubar".

   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                   and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                   and channel #bar using key "foobar".

   JOIN #foo,#bar                  ; join channels #foo and #bar.*/

void Join::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server){

    std::vector<std::string>tmp ;
    size_t found;
    std::vector<std::string>::const_iterator it= splitArgs.begin();
    for (; it < splitArgs.end() ; it++) {
        found = (*it).find(',');
        if ( found != std::string::npos) {
            tmp.push_back((*it).substr(0,found));
            found++;
            tmp.push_back((*it).substr(found, (*it).size()));
        }
        else{
            tmp.push_back(*it);
        }
    }
    std::vector<std::string>::const_iterator it2 = tmp.begin();
    found = 0;
    Channel *my_channel;
    for(;it2<tmp.end(); it2++)
    {
        found = (*it2).find('#') != std::string::npos ? (*it2).find('#') : (*it2).find('&')   ;
        if ( found != std::string::npos) {
            my_channel =  server.createChannel((*it2).substr(found + 1,(*it2).size()));
            my_channel->AddUser(new NormalUser(*user.second));
            found++;
        }
    }
}


