#include "Ping.hpp"

class NormalUser;

Ping::Ping() : ACommand("PING") {}

Ping::~Ping() {}

void
Ping::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    std::string message = ":ircserv PONG request received by [FT_IRC] \r\n";
    send(user.first, message.c_str(),message.size(), 0);
}
