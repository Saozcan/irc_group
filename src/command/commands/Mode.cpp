//
// Created by ebudak on 3/17/23.
//
#include "Mode.hpp"

Mode::Mode(): ACommand("MODE"){

}

Mode::~Mode() {

}
/*
 * MODE #Finnish +o Kilroy         ; Gives 'chanop' privileges to Kilroy on
 * 
 * */

void Mode::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server){
    if (splitArgs.size() < 4) {
        std::cout << "Syntax error\n";
        return ;
    }
    std::string channel_name = Utility::strTrim(splitArgs[1]);
    std::string targetUser = splitArgs[3];
    std::map<int , NormalUser*>::iterator it_user = server._users.begin();
    Channel* it_channel = server._channels.getChannel(channel_name);
    if(it_channel == nullptr)
    {
        std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), channel_name);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    NormalUser* tmpUser = it_channel->getUser(targetUser);
    if(tmpUser == nullptr)
    {
        std::string errMessage = ERR_NOSUCHNICK(user.second->getNick(), targetUser);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    size_t flag = splitArgs[2].find('+') != std::string::npos ? splitArgs[2].find('+') : splitArgs[2].find('-');
    if(flag == std::string::npos ){
        std::string errMessage = ERR_UNKNOWNMODE(user.second->getNick(), splitArgs[2]);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    if(!it_channel->checkOperators(user.second->getNick())){
        std::string errMessage = ERR_CHANOPRIVSNEEDED(user.second->getNick(), channel_name);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    std::string mode_flag = splitArgs[2];
    if(mode_flag == "+o"){
        it_channel->addMode(targetUser);
    }
    else if(mode_flag == "-o"){
        it_channel->removeMode(targetUser);
    }
    else {
        std::string errMessage = ERR_UNKNOWNMODE(user.second->getNick(), splitArgs[2]);
        Utility::sendToClient(user.first, errMessage);
    }
}