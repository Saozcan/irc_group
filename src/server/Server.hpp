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



        void createSocketFd();
        void acceptClient();
        int listenClients(std::vector<pollfd> &_clients, char* buffer);

        bool checkAndParseFirst(char *str, pollfd &poll);

    public:
        std::map<std::string, Channel*> _channels;
        std::map< int, NormalUser*> _users;
        std::string _pass;

        CommandExecuter _commands;

        Server();
        Server(std::string const &serverName, unsigned short port);
        ~Server();

        void listenServer();

//        //setters
//        void setHostName(const std::string &hostName);
//        void setServerName(const std::string &serverName);
//        void setPort(unsigned short port);
//
//        //getters
//        const std::string &getHostName() const;
//        const std::string &getServerName() const;
//        unsigned short getPort() const;
//
    Channel*  createChannel(std::string channelName);
//        void removeChannel(std::string channelName);
//
//        void addUser(AUser* user, int fd);
//        void removeUser(AUser* user, int fd);



};
