#include "irc.hpp"

int main(int argc, char const *argv[])
{
    //TODO :main arg alarak server kuracak
    Server server;

    User *usr = new User;
    Nick *nick = new Nick;
    Pass *pass = new Pass;
    Join *join = new Join;
    Mode *mode  = new Mode;
    server._commands.addCommand(usr);
    server._commands.addCommand(nick);
    server._commands.addCommand(pass);
    server._commands.addCommand(join);
    server._commands.addCommand(mode);


    server.listenServer();

//    std::cout << server.getServerName() << std::endl;
    /* code */
    return 0;
}
