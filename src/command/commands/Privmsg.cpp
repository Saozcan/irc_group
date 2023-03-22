#include "Privmsg.hpp"
#include "../../server/Server.hpp"

class Server;
class NormalUser;
class Channel;

Privmsg::Privmsg() : ACommand("PRIVMSG") {}

Privmsg::~Privmsg() {}

void
Privmsg::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 3) {
        std::cout << "Syntax Error" << std::endl;
        return ;
    }
    std::string sendMessage;
    sendMessage.append(user.second->getName() + ": ");
    for (int i = 2; i < splitArgs.size(); i++) {
        sendMessage += splitArgs[i];
        if (i == splitArgs.size() - 1)
            break;
        sendMessage += " ";
    }
    sendMessage.append("\n");
    if (splitArgs[1].find('#') != std::string::npos || splitArgs[1].find('&') != std::string::npos) {
        Channel *channel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        if(channel == nullptr){
            send(user.first, "Wrong channel name\n", strlen("Wrong channel name\n"), 0);
            return;
        }
        else
         channel->sendMessage(user.second->getName(), sendMessage);
    }
    else {
        std::map<int, NormalUser*>::iterator it = server._users.begin();
        for (; it != server._users.end(); it++) {
            if ((*it).second->getName() == splitArgs[1]) {
                send((*it).second->getPoll().fd, sendMessage.c_str(), strlen(sendMessage.c_str()), 0);
                break;
            }
        }
        if(it == server._users.end())
            send(user.first, "Wrong user name\n", strlen("Wrong user name\n"), 0);

    }
}
