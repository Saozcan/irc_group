#include "Pass.hpp"

Pass::Pass() : ACommand("PASS"){}

Pass::~Pass() {}

void Pass::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (user.second->getPass())
        send(user.first, "You already entered the pass.", strlen("You already entered the pass."), 0);
    if (splitArgs.size() > 1) {
        std::string argString;
        splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
        if (!strcmp(argString.c_str(), server._pass.c_str())) {
            user.second->setPass(true);
            send(user.first, "Pass accepted\n", strlen("Pass accepted\n"), 0);
        } else {
            send(user.first, "Please enter correct pass\n", strlen("Please enter correct pass\n"), 0);
        }
    } else {
        send(user.first, "Syntax error\n", strlen("Syntax error\n"), 0);
    }
}

//void Pass::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass) {
//    if (user.second->getPass())
//        send(user.first, "You already entered the pass.", strlen("You already entered the pass."), 0);
//    if (splitArgs.size() > 1) {
//        std::string argString;
//        splitArgs[1].find('\n') != std::string::npos ? argString = splitArgs[1].substr(0, splitArgs[1].size() - 1) : argString = splitArgs[1];
//        if (!strcmp(argString.c_str(), pass.c_str())) {
//            user.second->setPass(true);
//            send(user.first, "Pass accepted\n", strlen("Pass accepted\n"), 0);
//        } else {
//            send(user.first, "Please enter correct pass\n", strlen("Please enter correct pass\n"), 0);
//        }
//    } else {
//        send(user.first, "Syntax error\n", strlen("Syntax error\n"), 0);
//    }
//}
