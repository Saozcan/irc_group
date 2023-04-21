#pragma once

#include <iostream>
#include "vector"
#include "map"
#include "cstring"
#include <sys/socket.h>

#include "../user/NormalUser.hpp"
#include "../channel/Channel.hpp"
#include "../IRC_COMMAND.hpp"

class Utility;
class Server;

class ACommand
{
    private:
        std::string _name;
        
    public:
        ACommand();
        ACommand(const std::string& name);
        virtual ~ACommand();
        virtual void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server) = 0;
        void setName(const std::string& name);
        std::string getName();
};
