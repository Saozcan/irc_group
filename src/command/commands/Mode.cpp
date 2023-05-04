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
    if (splitArgs.size() < 2) {
        std::string errMessage = ERR_NEEDMOREPARAMS(user.second->getNick(), "MODE");
        Utility::sendToClient(user.first, errMessage);
        return ;
    }
    if (splitArgs.size() == 2 || splitArgs.size() == 3) {
        Channel* tmpChannel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        if(tmpChannel == NULL){
            std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), splitArgs[1]);
            Utility::sendToClient(user.first, errMessage);
            return;
        }
        std::string modes = tmpChannel->getOperators();
        std::vector<std::string> modeList = Utility::split(modes, " ");
        for (size_t i = 0; i < modeList.size(); i++) {
            std::string modeMessage = "MODE " + splitArgs[1] + " +o " + modeList[i] + "\r\n";
            Utility::sendToClient(user.first, modeMessage);
        }
        return ;
    }
    std::string channel_name = Utility::strTrim(splitArgs[1]);
    std::string targetUser = splitArgs[3];
    Channel* it_channel = server._channels.getChannel(channel_name);
    if(it_channel == NULL)
    {
        std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), channel_name);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    NormalUser* tmpUser = it_channel->getUser(targetUser);
    if(tmpUser == NULL)
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
        std::string modeMessage = "+o " + splitArgs[3];
        it_channel->sendMode(user.first, modeMessage);
    }
    else if(mode_flag == "-o"){
        it_channel->removeMode(targetUser);
        std::string modeMessage = "+o " + splitArgs[3];
        it_channel->sendMode(user.first, modeMessage);
    }
    else {
        std::string errMessage = ERR_UNKNOWNMODE(user.second->getNick(), splitArgs[2]);
        Utility::sendToClient(user.first, errMessage);
    }
}
