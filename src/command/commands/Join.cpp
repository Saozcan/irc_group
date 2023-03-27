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

void Join::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server) {

    std::vector<std::string> tmp;
    size_t found;
    std::vector<std::string>::const_iterator it = splitArgs.begin() + 1;
    for (; it < splitArgs.end(); it++) {
        found = (*it).find(',');
        if (found != std::string::npos) {
            tmp.push_back((*it).substr(0, found));
            found++;
            tmp.push_back((*it).substr(found, (*it).size()));
        } else {
            tmp.push_back(*it);
        }
    }
    std::vector<std::string>::const_iterator it2 = tmp.begin();
    Channel *my_channel;
    std::string foundtrim;
    for (; it2 < tmp.end(); it2++) {
        found = (*it2).find('#') != std::string::npos ? (*it2).find('#') : (*it2).find('&');
        if (found != std::string::npos) {
            foundtrim = Utility::strTrim((*it2));
            my_channel = server._channels.createChannel(foundtrim);
            my_channel->AddUser(user.second);
            std::string sendString =
                    ":ircserv 331 " + user.second->getName() + " #" + foundtrim + " :No topic is set\r\n";
            if (my_channel->isEmpty())
                sendString +=
                        ":ircserv 353 " + user.second->getName() + " = #" + foundtrim + " :@" + user.second->getName() +
                        "\r\n";
            sendString += ":ircserv 366 " + user.second->getName() + " #" + foundtrim + " :End of /NAMES list \r\n";
            send(user.first, sendString.c_str(), sendString.size(), 0);
        }
    }
}
