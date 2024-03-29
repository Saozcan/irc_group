#include "irc.hpp"

bool portCheck(std::string port)
{
    for (size_t i = 0; i < port.length(); i++) {
        if (!isdigit(port[i]))
            return false;
    }
    return true;
}

bool portRange(const std::string& port)
{
    int portNum = std::atoi(port.c_str());
    if (portNum < 1024 || portNum > 65535)
        return false;
    return true;
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cerr << "Argument Error\n";
        return 0;
    }
    if (!portCheck(argv[1]) || !portRange(argv[1]) || strlen(argv[2]) < 3) {
        std::cerr << "Argument Error\n";
        return 0;
    }
    try {
        unsigned short number = (unsigned short) strtoul(argv[1], NULL, 0);
        std::string password(argv[2]);
        Server server(number, password);

        server._commands.addCommand(new User);
        server._commands.addCommand(new Nick);
        server._commands.addCommand(new Pass);
        server._commands.addCommand(new Join);
        server._commands.addCommand(new Mode);
        server._commands.addCommand(new Help);
        server._commands.addCommand(new Privmsg);
        server._commands.addCommand(new Kick);
        server._commands.addCommand(new Notice);
        server._commands.addCommand(new Ping);
        server._commands.addCommand(new Part);
        server._commands.addCommand(new Quit);
        server._commands.addCommand(new Who);

        server.listenServer();
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
