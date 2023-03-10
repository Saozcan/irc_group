#include <iostream>
#include <map>
#include "../channel/Channel.hpp"
#include "../user/AUser.hpp"


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
        std::string _port;

        std::map<std::string, Channel*> _channels;
        std::map<std::string, AUser*> _users;
    public:
        Server();
        Server(std::string const &hostName, std::string const &serverName, std::string const &port);
        ~Server();

        //setters
        void setHostName(const std::string &hostName);
        void setServerName(const std::string &serverName);
        void setPort(const std::string& port);

        //getters
        const std::string &getHostName() const;
        const std::string &getServerName() const;
        const std::string &getPort() const;

        void addChannel(Channel* channel);
        void removeChannel(Channel* channel);

        void addUser(AUser* user);
        void removeUser(AUser* user);
};
