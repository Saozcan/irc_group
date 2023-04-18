#include "irc.hpp"

int main(int argc, char const *argv[])
{
    //TODO :main arg alarak server kuracak
//
//    if (argc != 3) {
//        std::cout << "Argument Error\n";
//        return 0;
//    }
    try {
//        unsigned short number = (unsigned short) strtoul(argv[1], NULL, 0);
//        std::string password(argv[2]);
//        Server server(number, password);
        Server server;

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

        server.listenServer();
    }
    catch(std::exception &e){
        std::cout << e.what();
    }

    return 0;
}
