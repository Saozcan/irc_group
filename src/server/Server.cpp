#include "Server.hpp"

enum loop {
    BREAK,
    CONTINUE,
};

Server::Server() {
    _serverName = "ircserv";
    _port = 8050;
    _pass = "123abc";
    _addrlen = sizeof(_address);
}

//TODO: PDF e göre args ayarlanacak.
Server::Server(std::string const &serverName, unsigned short port)
{
    _serverName = serverName;
    _port = port;
    _addrlen = sizeof(_address);
};

Server::~Server() {
    #pragma region FreeChannels
    std::map<std::string, Channel*>::iterator it = _channels.begin();
    std::map<int, NormalUser*>::iterator uIt = _users.begin();
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

void Server::listenServer() {
    this->createSocketFd();
    this->acceptClient();
}

void Server::createSocketFd() {
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { // Sock stream kullanılırsa TCP, sock dgram kullanılırsa UDP
        std::cout << "Socket creation error" << std::endl;
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);
    const int enable = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) //Sol_socket server olarak belirtir.
        std::cout << ("setsockopt(SO_REUSEADDR) failed") << std::endl;
    if (bind(_server_fd, (sockaddr*)&_address, sizeof(_address)) < 0) {
        std::cout << "Bind failed" << std::endl;
    }
    if (listen(_server_fd, 3) < 0) { // en fazla 3 kuyruk isteği alınabilir. Total client sayısı değildir.
        std::cout << "Listen failed" << std::endl;
    }
}

void Server::acceptClient() {
    std::vector<pollfd> _clients;

    char buffer[1024] = {0};
    fcntl(_server_fd, F_SETFL, O_NONBLOCK); // dinleme yaptığım server nonblock oldu
    while (true) {
        while (true) {
            if ((_new_socket = accept(_server_fd, (sockaddr*)&_address, (socklen_t*)&_addrlen)) < 0) {
                break;
            }
            struct pollfd tmp;
            tmp.fd = _new_socket;
            tmp.events = POLLIN; // ekstra için | kullanılabilir.
            send(tmp.fd, "Welcome to channel.\n", strlen("Welcome to channel.\n"), 0);
            _clients.push_back(tmp);
        }
        if (listenClients(_clients, buffer) == BREAK)
            break;
        else
            continue;
    }
}


int Server::listenClients(std::vector<pollfd> &_clients, char* buffer) {
    if (!_clients.empty()) {
        int pollReturn = poll(_clients.data(), _clients.size(), 1000);
//            std::cout << pollReturn << std::endl;
        if (pollReturn == -1) {
            perror("poll() error");
            return BREAK;
        }
        if (pollReturn == 0) {
            return CONTINUE;
        } // -1 hiç bekleme süresi koymaz
        for (std::vector<pollfd>::iterator it = _clients.begin(); it < _clients.end(); it++) {
            int requestCount = 0;
            if ((*it).revents & POLLIN) {
                int valread;
                while ((valread = recv((*it).fd, buffer, 1024, MSG_DONTWAIT)) > 0) { //MSG_DONT... non blcok için
                    buffer[valread] = '\0';
                    checkAndParseFirst(buffer, (*it));
                    memset(buffer, 0, strlen(buffer));
                }
                requestCount++;
                if (valread == 0) {
                    delete _users.find((*it).fd)->second;
                    _users.erase((*it).fd);
                    (*it).fd = -1;
                    (*it).events = 0;
                }
            }
            for (std::vector<pollfd>::iterator it = _clients.begin(); it < _clients.end(); ) {
                if ((*it).fd == -1) {
                    it = _clients.erase(it);
                } else {
                    ++it;
                }
            }
            if (requestCount == pollReturn)
                break ;
        }
    }
    return CONTINUE;
}

//void Server::setHostName(const std::string &hostName) {
//    _hostName = hostName;
//};
//
//void Server::setServerName(const std::string &serverName) {
//    _serverName = serverName;
//}
//
//void Server::setPort(unsigned short port) {
//    _port = port;
//};
//
//const std::string &Server::getHostName() const {
//    return _hostName;
//}
//
//const std::string &Server::getServerName() const {
//    return _serverName;
//}
//
//unsigned short Server::getPort() const {
//    return _port;
//}
//
Channel *Server::createChannel(std::string channelName){
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    Channel * my_channel;
    if(it == _channels.end()){
        _channels.insert(std::pair<std::string, Channel *>(channelName,new Channel(channelName) ));
        std::cout << std::endl << "A new channel created" << std::endl;
        my_channel = (_channels.find(channelName)->second);
        return my_channel;
    }
    return (*it).second;
}

//
//void Server::removeChannel(Channel *channel) {
//    _channels.erase(channel->getChannelName());
//}
//
//void Server::addUser(AUser *user, int fd) {
//    _users.insert(std::pair<int, AUser*>(fd, user));
//}
//
//void Server::removeUser(AUser *user, int fd) {
//    _users.erase(fd);
//}

bool Server::checkAndParseFirst(char *str, pollfd &poll)
{
    std::cout << _users.size() << std::endl;
    if (_users.find(poll.fd) == _users.end()) {
        NormalUser* newUser = new NormalUser;
        _users.insert(std::pair<int, NormalUser *>(poll.fd, newUser));
    }
    std::map<int, NormalUser*>::iterator it = _users.find(poll.fd);
    std::string buffer(str);
    std::vector<std::string> splitSpace = Utility::split(buffer, " ");
    if (it->second->getAllCheck()) {
        // TODO: Command kısmı burada çalışacak
    } else {
        if (splitSpace.size() > 1) { // TODO: Sadece pass varsa user ve nick komutları için geçerli
            if (_commands.executeCommand(splitSpace, (*it), *this)) {}
            else {
                send(poll.fd, "Please finish your profile.", strlen("Please finish your profile."), 0);
            }
        }
    }
    return false;
}


