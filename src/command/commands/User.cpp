#include "User.hpp"

User::User() : ACommand("USER"){}

User::~User() {}

void User::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (!user.second->getPass()) {
        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
        return ;
    }
    if (splitArgs.size() < 4) {
        send(user.first, "USER <username> <hostname> <servername> <real name>\n",
             strlen("USER <username> <hostname> <servername> <real name>\n"), 0);
        return ;
    }
    std::string argString = Utility::strTrim(splitArgs[1]);
    std::map<int, NormalUser*>::iterator it = server._users.begin();
    for (; it != server._users.end(); it++) {
        if (argString == it->second->getName()) {
            send(user.first, "There is a user with the specified name\n", strlen("There is a user with the specified name\n"), 0);
            return ;
        }
    }
    user.second->setName(argString);
    user.second->setHostname(splitArgs[2]);
    user.second->setServerName(splitArgs[3]);
    std::string realName;
    for (int i = 3; i < splitArgs.size(); i++) {
        realName += splitArgs[i];
        realName += " ";
    }
    user.second->setRealName(realName);
    send(user.first, "User changed\n", strlen("User changed\n"), 0);
    if (!user.second->getAllCheck() && user.second->getNick().size() > 1)
        user.second->setAllCheck(true);
}
