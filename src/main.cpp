#include "irc.hpp"

bool portCheck(std::string port)
{
    for (int i = 0; i < port.length(); i++) {
        if (!isdigit(port[i]))
            return false;
    }
    return true;
}

bool portRange(std::string port)
{
    int portNum = std::stoi(port);
    if (portNum < 1024 || portNum > 65535)
        return false;
    return true;
}

int main(int argc, char const *argv[])
{
    if (argc != 3 && portCheck(argv[1]) && portRange(argv[1]) && strlen(argv[2]) < 3) {
        std::cout << "Argument Error\n";
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
        std::cout << e.what();
    }

    return 0;
}
