#include "Pass.hpp"

Pass::Pass() : ACommand("PASS"){}

Pass::~Pass() {}

void Pass::execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server)
{
    if (user.second->getPass()) {
        send(user.first, "You already entered the pass.\n", strlen("You already entered the pass.\n"), 0);
        return ;
    }
    if (splitArgs.size() == 2) {
        if (!strcmp(splitArgs[1].c_str(), server.getPass().c_str())) {
            user.second->setPass(true);
            send(user.first, "Pass accepted\n", strlen("Pass accepted\n"), 0);
        } else {
            send(user.first, "Please enter correct pass\n", strlen("Please enter correct pass\n"), 0);
        }
    } else {
        send(user.first, "Syntax error\n", strlen("Syntax error\n"), 0);
    }
}
