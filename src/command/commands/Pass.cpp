#include "Pass.hpp"

Pass::Pass() : ACommand("PASS"){}

Pass::~Pass() {}

void Pass::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (user.second->getPass()) {
        Utility::sendToClient(user.first, ERR_ALREADYREGISTERED(user.second->getPrefix()));
        return ;
    }
    if (splitArgs.size() == 2) {
        if (!strcmp(splitArgs[1].c_str(), server.getPass().c_str())) {
            user.second->setPass(true);
			std::string noticeMsg("[FT_IRC]-/Enter <NICK> your_nick Than <USER> your nick, port, server name, fullname\n");
            Utility::sendToClient(user.first, noticeMsg);
        } else {
            Utility::sendToClient(user.first, ERR_PASSWDMISMATCH(user.second->getPrefix()));
        }
    } else {
        Utility::sendToClient(user.first, ERR_NEEDMOREPARAMS(user.second->getPrefix(), "PASS"));
    }
}
