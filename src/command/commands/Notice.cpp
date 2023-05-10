#include "Notice.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;
class Server;

Notice::Notice() : ACommand("NOTICE") {}

Notice::~Notice() {}

void
Notice::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 3) {
        Utility::sendToClient(user.first, ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]));
        return ;
    }
    std::string sendMessage;
    sendMessage.append(user.second->getPrefix() + " PRIVMSG " + splitArgs[1] + " ");
    for (size_t i = 2; i < splitArgs.size(); i++) {
        sendMessage += splitArgs[i];
        if (i == splitArgs.size() - 1)
            break;
        sendMessage += " ";
    }
    sendMessage.append("\r\n");
    if (splitArgs[1].find('#') != std::string::npos || splitArgs[1].find('&') != std::string::npos) {
        Channel *channel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        channel->sendMessage(user.second->getNick(), sendMessage, true);
    }
    else {
        std::map<int, NormalUser*>::iterator it = server._users.begin();
        for (; it != server._users.end(); it++) {
            if ((*it).second->getNick() == splitArgs[1]) {
                Utility::sendToClient(it->second->getPoll().fd, sendMessage);
                break;
            }
        }
    }
}
