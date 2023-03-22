#include "irc.hpp"

int main(int argc, char const *argv[])
{
    //TODO :main arg alarak server kuracak

    if (argc != 3) {
        std::cout << "Argument Error\n";
        return 0;
    }
    unsigned short number = (unsigned short) strtoul(argv[1], NULL, 0);
    std::string password(argv[2]);
    Server server(number, password);

    User *usr = new User;
    Nick *nick = new Nick;
    Pass *pass = new Pass;
    Join *join = new Join;
    Mode *mode  = new Mode;
    Help *help = new Help;
    Privmsg *privmsg = new Privmsg;
    Kick* kick = new Kick;
    Notice *notice = new Notice;
    server._commands.addCommand(usr);
    server._commands.addCommand(nick);
    server._commands.addCommand(pass);
    server._commands.addCommand(join);
    server._commands.addCommand(mode);
    server._commands.addCommand(help);
    server._commands.addCommand(privmsg);
    server._commands.addCommand(kick);
    server._commands.addCommand(notice);

    server.listenServer();

    return 0;
}
