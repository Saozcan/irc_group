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

    if (splitArgs.size() < 2)
    {
        std::string errorMsg = ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]);
        Utility::sendToClient(user.first, errorMsg);
    }
    else
    {
        std::string channel_name = splitArgs[1];
        Channel *channelPtr = server._channels.getChannel(channel_name);
        if (channelPtr != nullptr)
        {
            channelPtr->addUser(user.second);
            std::string sendMsg = RPL_JOIN1(user.second->getNick(), user.second->getHostname(), channel_name);
            sendMsg.append("\r\n");
            channelPtr->sendMessage(user.second->getNick(), sendMsg, false);
        }
        else if (channel_name.size() > 1 && (channel_name[0] == '&' || channel_name[0] == '#'))
        {
            channelPtr = server._channels.createChannel(channel_name);
            channelPtr->addUser(user.second);
            channelPtr->addMode(user.second->getNick());
            std::string sendMsg = RPL_JOIN1(user.second->getNick(), user.second->getHostname(), channel_name);
            sendMsg.append("\r\n");
            Utility::sendToClient(user.first, sendMsg);
        }
        channelPtr->irc353(user.first);
        channelPtr->irc366(user.first);
    }
}






















