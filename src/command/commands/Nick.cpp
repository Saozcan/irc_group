#include "Nick.hpp"

Nick::Nick() : ACommand("NICK") {}

Nick::~Nick() {}

void Nick::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server)
{
    if (user.second->getNick() != "" && user.second->getPass() == true && user.second->getName() != "")
    {
        if (server.getUser(splitArgs[1]) != nullptr)
            Utility::sendToClient(user.first, ERR_NICKNAMEINUSE(splitArgs[1]));
        else
        {
            Utility::sendToClient(user.first, RPL_NICKNAMECHANGE(user.second->getNick(), splitArgs[1]));
            user.second->setNick(splitArgs[1]);
        }
        return;
    }
    if (!user.second->getPass())
    {
        Utility::sendToClient(user.first, ERR_NOTREGISTERED(user.second->getNick()));
        return;
    }
    if (splitArgs.size() < 2)
    {
        Utility::sendToClient(user.first, ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]));
        return;
    }
    std::string argString = splitArgs[1];
    if (server.getUser(argString) != nullptr)
    {
        Utility::sendToClient(user.first, ERR_NICKNAMEINUSE(argString));
    }
    else
    {
        user.second->setNick(argString);
    }
}
