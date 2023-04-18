#include "../server/Server.hpp"
#include "CommandExecuter.hpp"


CommandExecuter::CommandExecuter() {}

CommandExecuter::~CommandExecuter() {
#pragma region FreeChannels
    std::map<std::string, ACommand*>::iterator it = _commands.begin();
    while (it != _commands.end())
    {
        delete (*it).second;
        it++;
    }
    _commands.clear();
#pragma endregion
}

bool CommandExecuter::executeCommand(const std::vector<std::string>& splitArgs, std::pair<const int, NormalUser*>& user, Server&server){
    std::map<std::string, ACommand*>::iterator it = _commands.find(Utility::toUpper(splitArgs[0]));
    if (it != _commands.end()) {
        (*it).second->execute(splitArgs, user, server);
        return true;
    }
    else {
        std::cout << "Cannot find " << splitArgs[0] << " command!" << " Command size: " << splitArgs[0].size() << std::endl;
        return false;
    }
}

void CommandExecuter::addCommand(ACommand *Command) {
    _commands.insert(std::pair<std::string, ACommand*>(Command->getName(), Command));
}

void CommandExecuter::forgetCommand(ACommand *Command) {
    _commands.erase(Command->getName());
}

