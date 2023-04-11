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

    std::string channel_name = splitArgs[1];

    if (splitArgs.size() < 2)
    {
        std::string err_parameter = "461 " + user.second->getNick() + " " + splitArgs[0] + " :Not enough parameters\r\n";
        if (send(user.first, err_parameter.c_str(), err_parameter.length(), 0) == -1)
            throw std::runtime_error("SENDING PROBLEM");
    }
    else
    {
        Channel *channelPtr = server._channels.getChannel(channel_name);
        if (channelPtr != nullptr)
        {
            //Add user.second to the channel as a member
            channelPtr->AddUser(user.second);
            std::string rpl_join = RPL_JOIN1(user.second->getNick(), user.second->getHostname(), channel_name);
            rpl_join.append("\r\n");

//            map<std::string, Client*>::iterator it_channel = channel_members.find(channel_name);
            channelPtr->sendMessage(user.second->getNick(), rpl_join);
//            while (it_channel->first == channel_name && channel_members.end() != it_channel)
//            {
//                if (it_channel->first != channel_name)
//                    break;
//                send(it_channel->second->getSockFd(), rpl_join.c_str(), rpl_join.length(), 0);
//                it_channel++;
//            }
        }
        else if (channel_name.size() > 1 && (channel_name[0] == '&' || channel_name[0] == '#'))
        {
            //Added New Channel and set user.second to Admin.
            channelPtr = server._channels.createChannel(channel_name);
            channelPtr->AddUser(user.second);
//            channels.insert(make_pair(channel_name, make_pair(user.second, std::string(""))));
//            channel_members.insert(make_pair(channel_name, user.second));
            std::string rpl_join = RPL_JOIN1(user.second->getNick(), user.second->getHostname(), channel_name);
            rpl_join.append("\r\n");
            send(user.first, rpl_join.c_str(), rpl_join.length(), 0);
        }
        channelPtr->irc366(user.first);
    }
}
