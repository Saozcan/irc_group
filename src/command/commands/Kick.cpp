#include "Kick.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;
class Server;

Kick::Kick() : ACommand("KICK") {}

Kick::~Kick() {}

void
Kick::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 3) {
        send(user.first, "Syntax Error\n", strlen("Syntax Error\n"), 0);
        return ;
    }
    if (splitArgs[1].find('#') != std::string::npos || splitArgs[1].find('&') != std::string::npos) {
        Channel *channel = server._channels.getChannel(Utility::strTrim(splitArgs[1]));
        if(channel == nullptr){
            send(user.first, "Wrong channel name\n", strlen("Wrong channel name\n"), 0);
            return;
        }
        else {
            if (channel->checkOperators(user.second->getNick())) {
                for (int i = 2; i < splitArgs.size(); i++)
                    channel->leaveUser(splitArgs[i]);
            }
            else {
                send(user.first, "You are not an operator\n", strlen("You are not an operator\n"), 0);
                return ;
            }
        }
    }
}
