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
    std::string argString = Utility::strTrim(splitArgs[1]);
    std::cout << "argString Usser: >" << argString << " " << argString.size() << std::endl;
    user.second->setName(argString);
    send(user.first, "User changed\n", strlen("User changed\n"), 0);
    if (!user.second->getAllCheck() && user.second->getNick().size() > 1)
        user.second->setAllCheck(true);
}
