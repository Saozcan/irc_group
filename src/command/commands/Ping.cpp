#include "Ping.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Ping::Ping() : ACommand("PING") {}

Ping::~Ping() {}

void
Ping::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 2) {
        std::string message = ERR_NEEDMOREPARAMS(user.second->getNick(), "PING");
        Utility::sendToClient(user.first, message);
    }
    std::string message = ":ircserv PONG request received by [FT_IRC]\r\n";
    Utility::sendToClient(user.first, message);
}
