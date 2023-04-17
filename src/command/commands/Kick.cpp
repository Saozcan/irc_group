#include "Kick.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;
class Server;

Kick::Kick() : ACommand("KICK") {}

Kick::~Kick() {}

void
Kick::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 3) {
        std::string errMessage = ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]);
        Utility::sendToClient(user.first, errMessage);
        return ;
    }
    if (splitArgs[1].find('#') != std::string::npos || splitArgs[1].find('&') != std::string::npos) {
        Channel *channel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        if(channel == nullptr){
            std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), splitArgs[1]);
            Utility::sendToClient(user.first, errMessage);
            return;
        }
        else {
            if (channel->checkOperators(user.second->getNick())) {
                for (int i = 2; i < splitArgs.size(); i++)
                    channel->leaveUser(splitArgs[i]);

            }
            else {
                std::string errMessage = ERR_CHANOPRIVSNEEDED(user.second->getNick(), splitArgs[1]);
                Utility::sendToClient(user.first, errMessage);
                return ;
            }
        }
    }
}
