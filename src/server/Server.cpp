#include "Server.hpp"

Server::Server() {
    _hostName = "127.0.0.1";
    _serverName = "ircserv";
    _port = "1234";
}

Server::Server(std::string const &hostName, std::string const &serverName, std::string const &port)
{
    _hostName = hostName;
    _serverName = serverName;
    _port = port;
};

Server::~Server() {
    #pragma region FreeChannels
    std::map<std::string, Channel*>::iterator it = _channels.begin();
    std::map<std::string, AUser*>::iterator uIt = _users.begin();
    while (it != _channels.end())
    {
        delete (*it).second;
        it++;
    }
    _channels.clear();
    while (uIt != _users.end())
    {
        delete (*uIt).second;
        uIt++;
    }
    _users.clear();
    #pragma endregion
};

void Server::setHostName(const std::string &hostName) {
    _hostName = hostName;
};

void Server::setServerName(const std::string &serverName) {
    _serverName = serverName;
}

void Server::setPort(const std::string &port) {
    _port = port;
};

const std::string &Server::getHostName() const {
    return _hostName;
}

const std::string &Server::getServerName() const {
    return _serverName;
}

const std::string &Server::getPort() const {
    return _port;
}

void Server::addChannel(Channel *channel) {
    _channels.insert({channel->getChannelName(), channel});
}

void Server::removeChannel(Channel *channel) {
    _channels.erase(channel->getChannelName());
}

void Server::addUser(AUser *user) {
    _users.insert({user->getName(), user});
}

void Server::removeUser(AUser *user) {
    _users.erase(user->getName());
}


