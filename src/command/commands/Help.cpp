#include "Help.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Help::Help() : ACommand("HELP") {}

Help::~Help() {}

void
Help::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    std::string message = " First finish your profile\nPASS <pass>\nNICK <nick name>\nUSER <username> <hostname> <servername> <realname> \n";
    Utility::sendToClient(user.first, message);
}
