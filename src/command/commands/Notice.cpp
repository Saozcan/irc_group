#include "Notice.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;
class Server;

Notice::Notice() : ACommand("NOTICE") {}

Notice::~Notice() {}

void
Notice::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 2) {
        std::string errMessage = ERR_NEEDMOREPARAMS(user.second->getNick(), "NOTICE");
        Utility::sendToClient(user.first, errMessage);
        return ;
    }
    std::string message = "NOTICE: ";
    for (int i = 1; i < splitArgs.size(); i++) {
        message += splitArgs[i];
        if (i != splitArgs.size() - 1)
            message += " ";
    }
    message += "\r\n";
    size_t messageLen = message.size();
    std::map<int, NormalUser*>::iterator it = server._users.begin();
    for (; it != server._users.end(); it++) {
        if (user.first != it->first) {
            std::string sendMessage = (user.second->getPrefix() + " PRIVMSG " + splitArgs[1] + " ");
            for (int i = 2; i < splitArgs.size(); i++) {
                sendMessage += splitArgs[i];
                if (i == splitArgs.size() - 1)
                    break;
                sendMessage += " ";
            }
            sendMessage.append("\r\n");
            Utility::sendToClient(it->first, sendMessage);
        }
    }
}
