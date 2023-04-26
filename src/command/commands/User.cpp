#include "User.hpp"
#include "../../utility/Utility.hpp"

User::User() : ACommand("USER"){}

User::~User() {}

void User::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (user.second->getAllCheck() && !user.second->getNick().empty()) {
        Utility::sendToClient(user.first, ERR_ALREADYREGISTERED(user.second->getNick()));
        return ;
    }
    else if (!user.second->getPass()) {
        Utility::sendToClient(user.first, ERR_NOTREGISTERED(user.second->getNick()));
        return ;
    }
    else if (user.second->getNick().empty()) {
        Utility::sendToClient(user.first, ERR_NOTREGISTERED(user.second->getNick()));
        return ;
    }
    else if (splitArgs.size() < 5) {
        Utility::sendToClient(user.first, ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]));
        return ;
    }
    user.second->setUser(splitArgs[1]);
    user.second->setHostname(splitArgs[2]);
    user.second->setServerName(splitArgs[3]);
    user.second->setRealName(splitArgs);
    user.second->setAllCheck(true);
    user.second->setPrefix();
    Utility::sendToClient(user.first, RPL_WELCOME(user.second->getNick(), user.second->getName(), user.second->getHostname()));
    if (!user.second->getAllCheck() && !user.second->getNick().empty())
        user.second->setAllCheck(true);
    user.second->setPrefix();
}
