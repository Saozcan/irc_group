#include "Help.hpp"

class NormalUser;

Help::Help() : ACommand("HELP") {}

Help::~Help() {}

void
Help::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    send(user.first,"First finish your profile\nPASS <pass>\nNICK <nick name>\nUSER <username>\n",strlen("First finish your profile\nPASS <pass>\n NICK <nick name>\n USER <username>\n"), 0);
}
