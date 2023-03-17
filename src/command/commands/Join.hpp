#pragma once

#include "../ACommand.hpp"
#include "../../utility/Utility.hpp"
#include "iostream"

class Channel;
class NormalUser;
class Join : public ACommand {
public:
    Join();
    ~Join();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
//    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass);
private:
};