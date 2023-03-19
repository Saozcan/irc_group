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
    size_t flag;
    std::vector<std::string>::const_iterator it = splitArgs.begin() + 1;
    std::map<std::string , Channel*>::iterator it_channel = server._channels.begin();
    std::map<int , NormalUser*>::iterator it_user = server._users.begin();
    std::string user_name = *(it + 2);
    for(;it != splitArgs.end(); it++)
    {
        if(it != splitArgs.end())
        {   found = (*it).find('#') != std::string::npos ? (*it).find('#') : (*it).find('&');
//            it = it + 1;
//            flag = (*(it)).find('+') != std::string::npos ? (*(it)).find('+') : (*(it)).find('-');
        }
        if (found != std::string::npos) {
            for (; it_channel != server._channels.end(); it_channel++) {
                it_channel = server._channels.find((*(it - 1)).substr(found + 1, (*(it - 1)).size()));
                if (!it_channel->first.empty())
                    break;
            }
                    if(!it_channel->first.empty())
                    {
                        for (; it_user != server._users.end() ; it_user++) {
                               int foundN =  user_name.find('\n');
                               if(foundN != std::string::npos)
                                    user_name = user_name.substr(0, foundN);
                            if(user_name.compare((*it_user).second->getName()) == 0){
                                it_channel->second->addMode(user_name);
                                std::cout << "User added as operator"<< std::endl;
                            }
                        }
                    }
                    else{
                    std::cout << "channel yok" << std::endl;
                        break;
                    }
        }
        else {
            std::cout << "We don't have such a channel!\nHint: JOIN command create new channel" << std::endl;
            break;
        }
    }
}


