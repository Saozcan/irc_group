#include "Who.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Who::Who() : ACommand("WHO") {}

Who::~Who() {}

void
Who::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
	if (splitArgs.size() < 2) {
        std::string errMessage = ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]);
        Utility::sendToClient(user.first, errMessage);
        return ;
    }
if (splitArgs[1].find('#') != std::string::npos || splitArgs[1].find('&') != std::string::npos) {
        Channel *channel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        if(channel == NULL){
            std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), splitArgs[1]);
            Utility::sendToClient(user.first, errMessage);
            return;
        }
        else {
            channel->irc352(user.first);
            channel->irc315(user.first);
        }
    }
}
