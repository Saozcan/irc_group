#pragma once

#include <map>
#include "iostream"
#include "../user/NormalUser.hpp"
#include "../channel/Channel.hpp"
#include "../utility/Utility.hpp"

class ACommand;

class CommandExecuter
{
    private:
        std::map<std::string, ACommand*> _commands;

    public:
        CommandExecuter();

        ~CommandExecuter();

        bool executeCommand(const std::vector<std::string>& splitArgs, std::pair<const int, NormalUser*>& user, Server&server);

        void addCommand(ACommand* Command);

        void forgetCommand(ACommand* Command);
};
