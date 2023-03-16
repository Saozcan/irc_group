#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include "fcntl.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>


//#include "../user/AUser.hpp"
#include "../channel/Channel.hpp"
class Channel;
class AUser;


/**
 * userlarıda tutması gerek.
 *
 * Channel class'ı için message map datası tutulabilir.
 *
 */

class Server{
    private:
        std::string _hostName;
        std::string _serverName;
        unsigned short _port;

        int _server_fd;
        int _new_socket;
        struct sockaddr_in _address;
        int _enable;

        struct pollfd _pollfd[1024];

        std::map<std::string, Channel*> _channels;
        std::map<std::string, AUser*> _users;
        std::map<std::string, AParse *> _parsers;

        void createSocketFd();
        void acceptClient();
    public:
        Server();
        Server(std::string const &hostName, std::string const &serverName, unsigned short port);
        ~Server();

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
};


