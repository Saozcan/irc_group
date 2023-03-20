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
    std::string channel_name = Utility::strTrim(splitArgs[1]);
    std::string targetUser = Utility::strTrim(splitArgs[3]);
    std::map<int , NormalUser*>::iterator it_user = server._users.begin();
    std::map<std::string , Channel*>::iterator it_channel = server._channels.find(channel_name);
    bool checkUser = false;
    if(it_channel == server._channels.end())
    {
        std::cout << "There is no such channel" << std::endl;
        return;
    }
    for (; it_user != server._users.end() ; it_user++) {
        if(targetUser == (*it_user).second->getName()) {
            checkUser = true;
        }
    }
    if(!checkUser)
    {
        std::cout << "There is no such user" << std::endl;
        return;
    }
    size_t flag = splitArgs[2].find('+') != std::string::npos ? splitArgs[2].find('+') : splitArgs[2].find('-');
    if(flag == std::string::npos ){
        std::cout << "Enter mode flag for operation" << std::endl;
        return;
    }
    if(!it_channel->second->checkOperators(user.second->getName())){
        std::cout << "You are not an operator" << std::endl;
        return;
    }
    std::string mode_flag = splitArgs[2];
    if(mode_flag == "+o"){
        it_channel->second->addMode(targetUser);
        std::cout << targetUser <<": User added as an operator"<< std::endl;
    }
    else if(mode_flag == "-o"){
        it_channel->second->removeMode(targetUser);
        std::cout << targetUser << ": User removed as an operator" << std::endl;
    }
    else
        std::cout << "Invalid mode flag" << std::endl;
}