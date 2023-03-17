#include "irc.hpp"

int main(int argc, char const *argv[])
{
    Server server;

    User *usr = new User;
    Nick *nick = new Nick;
    Pass *pass = new Pass;
    Join *join = new Join;
    server._commands.addCommand(usr);
    server._commands.addCommand(nick);
    server._commands.addCommand(pass);

    server._commands.addCommand(join);

    server.listenServer();

//    std::cout << server.getServerName() << std::endl;
    /* code */
    return 0;
}
