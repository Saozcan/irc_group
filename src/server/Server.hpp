#pragma once

#include <iostream>
#include <string.h>
#include "fcntl.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#include "../irc.hpp"
#include "../channel/Channel.hpp"
#include "../command/CommandExecuter.hpp"
#include "../user/NormalUser.hpp"
#include "../utility/Utility.hpp"
#include "../channel/ChannelBook.hpp"

/**
 * userlarıda tutması gerek.
 *
 * Channel class'ı için message map datası tutulabilir.
 *
 */

class Server
{
private:
    std::string _serverName;
    unsigned short _port;

    int _server_fd;
    int _new_socket;
    struct sockaddr_in _address;
    int _addrlen;

    std::string _pass;

    void createSocketFd();
    void acceptClient();
    int listenClients(std::vector<pollfd> &_clients, char *buffer);
    bool checkAndParseFirst(char *str, pollfd &poll);

public:
    std::map<int, NormalUser *> _users;
    CommandExecuter _commands;
    ChannelBook _channels;

    Server();
    Server(unsigned short port, std::string &password);
    ~Server();

    void listenServer();

    std::string getPass();
    NormalUser *getUser(const std::string &nick);

    class WrongPort : public std::exception
    {
        const char *what() throw()
        {
            return "port have to be 1024 <port> 65535\n";
        }
    };
};
