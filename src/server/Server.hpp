#pragma once

#include <iostream>
#include <string.h>
#include "fcntl.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include "../../irc.hpp"

#include "../channel/Channel.hpp"
#include "../command/CommandExecuter.hpp"

class Channel;
class AUser;

/**
 * userlarıda tutması gerek.
 *
 * Channel class'ı için message map datası tutulabilir.
 *
 */

class Server
{
    private:
        std::string _hostName;
        std::string _serverName;
        std::string _pass;
        unsigned short _port;

        int _server_fd;
        int _new_socket;
        struct sockaddr_in _address;
        int _addrlen;

        std::map<std::string, Channel*> _channels;
        std::map<std::string, AUser*> _users;

        void createSocketFd();
        void acceptClient();
        int listenClients(std::vector<pollfd> &_clients, char* buffer);
        int listenNotActiveClients(std::vector<pollfd> &_clients, std::vector<pollfd>& notActiveClients, std::vector<int> &check, char* buffer);

        bool checkAndParseFirst(char *str, pollfd &poll, int& checkIt);

    public:
        CommandExecuter _commands;

        Server();
        Server(std::string const &hostName, std::string const &serverName, unsigned short port);
        ~Server();

        void listenServer();

        //setters
        void setHostName(const std::string &hostName);
        void setServerName(const std::string &serverName);
        void setPort(unsigned short port);

        //getters
        const std::string &getHostName() const;
        const std::string &getServerName() const;
        unsigned short getPort() const;

        void addChannel(Channel* channel);
        void removeChannel(Channel* channel);

        void addUser(AUser* user);
        void removeUser(AUser* user);

    static bool checkAndParse(Server &server, pollfd &poll, char* str);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    static std::string& toUpper(std::string &str);

};
