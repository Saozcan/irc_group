#pragma once

#include "../ACommand.hpp"
#include "iostream"

class Channel;
class NormalUser;
class Notice : public ACommand {
public:
    Notice();
    ~Notice();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
private:
};