#include "User.hpp"

User::User() : ACommand("USER"){}

User::~User() {}

void User::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    //TODO: userName unique olacaksa kontrol edilecek.
    if (!user.second->getPass()) {
        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
        return ;
    }
    std::string argString;
    splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
    user.second->setName(argString);
    send(user.first, "User changed\n", strlen("User changed\n"), 0);
    if (!user.second->getAllCheck() && user.second->getNick().size() > 1)
        user.second->setAllCheck(true);
}

//void User::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass) {
//    //TODO: userName unique olacaksa kontrol edilecek.
//    if (!user.second->getPass()) {
//        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
//        return ;
//    }
//    std::string argString;
//    splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
//    user.second->setName(argString);
//    send(user.first, "User changed\n", strlen("User changed\n"), 0);
//    if (!user.second->getAllCheck() && user.second->getNick().size() > 1)
//        user.second->setAllCheck(true);
//}