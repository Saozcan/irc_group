#include "Server.hpp"

Server::Server() {
    _hostName = "127.0.0.1";
    _serverName = "ircserv";
    _port = 1234;
    this->createSocketFd();
    this->acceptClient();
}

Server::Server(std::string const &hostName, std::string const &serverName, unsigned short port)
{
    _hostName = hostName;
    _serverName = serverName;
    _port = port;
    this->createSocketFd();
    this->acceptClient();
};

Server::~Server() {
//    #pragma region FreeChannels
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
//    #pragma endregion
};

void Server::createSocketFd() {
    //createFd
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1)
        std::cout << "Error\n";
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);

    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &_enable, sizeof(int)) < 0)
        std::cout << ("setsockopt(SO_REUSEADDR) failed") << std::endl;

    //bind
    if (listen(_server_fd, 3) < 0)
        std::cout << "Listen failed" << std::endl;
}

void Server::acceptClient() {
    int index = 0;
    char buffer[1024] = {0};
    fcntl(_server_fd, F_SETFL, O_NONBLOCK);
    socklen_t address_size = sizeof(_address);

    while (true) {
        while (true) {
            if ((_new_socket = accept(_server_fd, (sockaddr*)&_address, &address_size)) < 0){
                break;
            }
            _pollfd[index].fd = _new_socket;
            _pollfd[index].events = POLLIN;
            send(_pollfd[index].fd, "Hello", strlen("Hello"), 0);
            index++;
        }
        if (index > 0) {
            int pollReturn = poll(_pollfd, index, 1000);
            if (pollReturn == 0) {
                continue;
            }
            for (int i = 0; i < index; i++) {
                int requestCount = 0;
                if (_pollfd[i].revents & POLLIN) {
                    int valread;
                    while ((valread = recv(_pollfd[i].fd, buffer, 1024, MSG_DONTWAIT)) > 0) {
                        buffer[valread] = '\0';
                        parse_irc_message(buffer);
//                        std::vector<std::string> spliteArgs = splite(buffer, " ");
//                        it = _parsers.find(spliteArgs[0]);
//                        (*it).second::parse_for_command(spliteArgs, *this);
                        std::cout << "Client: " << buffer << std::endl;
                        send(_pollfd[i].fd, "I'll take it\n", strlen("I'll take it\n"),0 );
                        memset(buffer, 0, sizeof(buffer));
                    }
                    requestCount++;
                    if (valread == 0) {
                        _pollfd[i].fd = -1;
                        _pollfd[i].events = 0;
                    }
                }
                if (requestCount == pollReturn)
                    break;
            }
        }
    }
}

void Server::setHostName(const std::string &hostName) {
    _hostName = hostName;
};

void Server::setServerName(const std::string &serverName) {
    _serverName = serverName;
}

void Server::setPort(unsigned short port) {
    _port = port;
};

const std::string &Server::getHostName() const {
    return _hostName;
}

const std::string &Server::getServerName() const {
    return _serverName;
}

unsigned short Server::getPort() const {
    return _port;
}

void Server::addChannel(Channel *channel) {
    _channels.insert(std::make_pair(channel->getChannelName(), channel));
}

void Server::removeChannel(Channel *channel) {
    _channels.erase(channel->getChannelName());
}

void Server::addUser(AUser *user) {
    _users.insert(std::make_pair(user->getName(), user));
}

void Server::removeUser(AUser *user) {
    _users.erase(user->getName());
}


