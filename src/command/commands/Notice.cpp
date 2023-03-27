#include "Notice.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;
class Server;

Notice::Notice() : ACommand("NOTICE") {}

Notice::~Notice() {}

void
Notice::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 2) {
        send(user.first, "Syntax Error\n", strlen("Syntax Error\n"), 0);
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
        if (user.first != it->first)
        send(it->first, message.c_str(), messageLen, 0);
    }
}
