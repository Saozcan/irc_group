#include "Server.hpp"

Server::Server() {
    _hostName = "127.0.0.1";
    _serverName = "ircserv";
    _port = 8050;
    _addrlen = sizeof(_address);
    this->createSocketFd();
    this->acceptClient();
}

Server::Server(std::string const &hostName, std::string const &serverName, unsigned short port)
{
    _hostName = hostName;
    _serverName = serverName;
    _port = port;
    _addrlen = sizeof(_address);
    this->createSocketFd();
    this->acceptClient();
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

void Server::createSocketFd() {
    //createFd
    // Creating a socket file descriptor

    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { // Sock stream kullanılırsa TCP, sock dgram kullanılırsa UDP
        std::cout << "Socket creation error" << std::endl;
    }

    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);
    std::cout << htons(_port) << std::endl;

    const int enable = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) //Sol_socket server olarak belirtir.
        std::cout << ("setsockopt(SO_REUSEADDR) failed") << std::endl;


    // Bind the socket to the specified _address and _port
    if (bind(_server_fd, (sockaddr*)&_address, sizeof(_address)) < 0) {
        std::cout << "Bind failed" << std::endl;
    }

    // Listen for incoming connections
    if (listen(_server_fd, 3) < 0) { // en fazla 3 kuyruk isteği alınabilir. Total client sayısı değildir.
        std::cout << "Listen failed" << std::endl;
    }

}

void Server::acceptClient() {
    char buffer[1024] = {0};
    unsigned int index = 0;

    fcntl(_server_fd, F_SETFL, O_NONBLOCK); // dinleme yaptığım server nonblock oldu

    // Accept incoming connections and echo messages back to the client
    while (true) {

        while (true) {

            if ((_new_socket = accept(_server_fd, (sockaddr*)&_address, (socklen_t*)&_addrlen)) < 0) {
                break;
            }
            _pollfd[index].fd = _new_socket;
            _pollfd[index].events = POLLIN; // ekstra için | kullanılabilir.
            send(_pollfd[index].fd, "Welcome to channel.", strlen("Welcome to channel."), 0);
            index++;

        }

        if (index > 0) {
            int pollReturn = poll(_pollfd, index, 1000);
            if (pollReturn == 0) {
                continue;
            } // -1 hiç bekleme süresi koymaz

            std::cout << index << std::endl;

            for (int i = 0; i < index; i++) {
                int requestCount = 0;
                if (_pollfd[i].revents & POLLIN) {
                    int valread;
                    while ((valread = recv(_pollfd[i].fd, buffer, 1024, MSG_DONTWAIT)) > 0) { //MSG_DONT... non blcok için
                        buffer[valread] = '\0';
                        std::cout << "Client: " << buffer << std::endl;
                        send(_pollfd[i].fd, buffer, strlen(buffer), 0);
                        memset(buffer, 0, sizeof(buffer));
                    }
                    requestCount++;
                    if (valread == 0 ) {
                        _pollfd[i].fd = -1;
                        _pollfd[i].events = 0; // If there is no messages it will clean it
                    }
//                    _pollfd[i].fd = -1; // -1 ignore yani temizlemiş olur.
                }
                if (requestCount == pollReturn)
                    break ;
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


