#include "Quit.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Quit::Quit() : ACommand("QUIT") {}

Quit::~Quit() {}

void
Quit::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 2) {
        std::string message = RPL_QUIT(user.second->getHostname(), "Time to launch the nukes");
        Utility::sendToClient(user.first, message);
    }
    else {
        std::string message = RPL_QUIT(user.second->getHostname(), splitArgs[1]);
        Utility::sendToClient(user.first, message);
    }
    server._channels.quitUser(user.second->getNick());
    server._users.erase(user.first);
    close(user.first);
}
