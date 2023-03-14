#include "irc.hpp"

int main(int argc, char const *argv[])
{
    Server server;

    User *usr = new User;
    Nick *nick = new Nick;

    server._commands.addCommand(usr);
    server._commands.addCommand(nick);

    server.listenServer();

    std::cout << server.getServerName() << std::endl;
    /* code */
    return 0;
}
