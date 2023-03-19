#pragma once

#include "../ACommand.hpp"
#include "../../utility/Utility.hpp"
#include "iostream"

using std::cout;
using std::endl;
class Channel;
class NormalUser;
class Mode : public ACommand {
public:
    Mode();
    ~Mode();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
//    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass);
private:
};