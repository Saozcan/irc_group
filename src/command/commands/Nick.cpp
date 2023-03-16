#include "Nick.hpp"


Nick::Nick() : ACommand("NICK"){}

Nick::~Nick() {}

void Nick::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    //TODO: nick unique olacaksa kontrol edilecek.
    if (!user.second->getPass()) {
        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
        return ;
    }
    std::string argString;
    splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
    user.second->setNick(argString);
    send(user.first, "Nick changed\n", strlen("Nick changed\n"), 0);
    if (!user.second->getAllCheck() && user.second->getName().size() > 1)
        user.second->setAllCheck(true);
}

//void Nick::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass) {
//    //TODO: nick unique olacaksa kontrol edilecek.
//    if (!user.second->getPass()) {
//        send(user.first, "Please enter pass\n", strlen("Please enter pass\n"), 0);
//        return ;
//    }
//    std::string argString;
//    splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
//    user.second->setNick(argString);
//    send(user.first, "Nick changed\n", strlen("Nick changed\n"), 0);
//    if (!user.second->getAllCheck() && user.second->getName().size() > 1)
//        user.second->setAllCheck(true);
//}