#include "ACommand.hpp"
#include "Commands.hpp"
#include <map>

class CommandExecuter
{
    private:
        std::map<std::string, ACommand*> _commands;

    public:
        CommandExecuter();

        ~CommandExecuter();

        void executeCommand(std::string command);

        void addCommand(ACommand* Command);

        void forgetCommand(ACommand* Command);
};
