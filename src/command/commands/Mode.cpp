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
    size_t found;
    std::string channel_name;
    std::string new_user;
    std::vector<std::string>::const_iterator it = splitArgs.begin() + 1;
    std::map<std::string , Channel*>::iterator it_channel;
    std::map<int , NormalUser*>::iterator it_user = server._users.begin();

    std::string user_name = Utility::strTrim(*(it + 2));
    found = (*it).find('#') != std::string::npos ? (*it).find('#') : (*it).find('&');
    channel_name = Utility::strTrim(*it);
    bool checkUser = false;
    if(found != std::string::npos)
    {
        it_channel = server._channels.find(channel_name);
        if (!it_channel->first.empty()){
            for (; it_user != server._users.end() ; it_user++) {
                if(user_name == (*it_user).second->getName()) {
                    checkUser = true;
                }
            }
            if(checkUser){
                std::string mode_flag = *(it + 1);
                if(!mode_flag.empty()){
                    if(it_channel->second->checkOperators(user.second->getName())){
                        if(mode_flag == "+o"){
                            it_channel->second->addMode(user_name);
                            std::cout << user_name <<": User added as an operator"<< std::endl;
                        }
                        else if(mode_flag == "-o"){
                            it_channel->second->removeMode(user_name);
                            std::cout << user_name << ": User removed as an operator" << std::endl;
                        }
                        else
                            std::cout << "Invalid mode flag" << std::endl;
                    }
                    else
                        std::cout << "Sorry you are not an operator" << std::endl;
                }
                else
                    std::cout << "Enter mode flag for operation" << std::endl;
            }
            else
                std::cout << "User cannot be found! " << std::endl;
        }
        else
            std::cout << "We don't have such a channel!\nHint: JOIN command create new channel" << std::endl;
    }
    else
            std::cout << "Please enter the channel name" << std::endl;
}