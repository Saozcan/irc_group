#pragma once

#include "../ACommand.hpp"

class Privmsg : public ACommand {
public:
    Privmsg();
    ~Privmsg();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
//    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass);
private:
};
