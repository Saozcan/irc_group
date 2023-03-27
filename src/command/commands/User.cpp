#include "User.hpp"

User::User() : ACommand("USER"){}

User::~User() {}

void User::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (!user.second->getPass()) {
        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
        return ;
    }
    if (user.second->getNick().empty()) {
        send(user.first, "Please enter NICK command first \r\n", strlen("Please enter NICK command first \r\n"), 0);
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
    std::string returnStr = ":ircserv 001 " + argString + " Welcome the Internet Relay Chat " + ":qwe!bla@127.0.0.1\r\n";

    send(user.first, returnStr.c_str(), returnStr.size(), 0);
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
    std::string replay = ":" + user.second->getNick() + "!" + user.second->getName() + "@" + user.second->getHostname();
    user.second->setReplay(replay);
}
