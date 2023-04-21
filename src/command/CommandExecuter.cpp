#include "../server/Server.hpp"
#include "CommandExecuter.hpp"


CommandExecuter::CommandExecuter() {}

CommandExecuter::~CommandExecuter() {
//#pragma region FreeChannels
    std::map<std::string, ACommand*>::iterator it = _commands.begin();
    while (it != _commands.end())
    {
        delete (*it).second;
        it++;
    }
    _commands.clear();
//#pragma endregion
}

bool CommandExecuter::executeCommand(const std::vector<std::string>& splitArgs, std::pair<const int, NormalUser*>& user, Server&server){
    std::map<std::string, ACommand*>::iterator it = _commands.find(Utility::toUpper(splitArgs[0]));
    if (it != _commands.end()) {
        (*it).second->execute(splitArgs, user, server);
        return true;
    }
    else {
        std::string errMessage = ERR_UNKNOWNCOMMAND(user.second->getNick(), splitArgs[0]);
        Utility::sendToClient(user.first, errMessage);
        return false;
    }
}

void CommandExecuter::addCommand(ACommand *Command) {
    _commands.insert(std::pair<std::string, ACommand*>(Command->getName(), Command));
}

void CommandExecuter::forgetCommand(ACommand *Command) {
    _commands.erase(Command->getName());
}

