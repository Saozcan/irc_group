#include "Server.hpp"

enum loop {
    BREAK,
    CONTINUE,
};

Server::Server() {
    _serverName = "ircserv";
    _port = 1234;
    _pass = "123";
    _addrlen = sizeof(_address);
}

//TODO: PDF e göre args ayarlanacak.
Server::Server(unsigned short port, std::string &password)
{
    if (port < 1024 || port > 65535) {
        throw Server::WrongPort();
    }
    _port = port;
    _pass = password;
    _addrlen = sizeof(_address);
};

Server::~Server() {
    // TODO: Ahmet'e sorulacak pragma...
    #pragma region FreeChannels
    std::map<int, NormalUser*>::iterator uIt = _users.begin();
    while (uIt != _users.end())
    {
        delete (*uIt).second;
        uIt++;
    }
    _users.clear();
    #pragma endregion
};

std::string Server::getPass() {
    return _pass;
}

NormalUser *Server::getUser(const std::string &nick)
{
    std::map<int, NormalUser*>::iterator uIt = _users.begin();
    while (uIt != _users.end())
    {
        if ((*uIt).second->getNick() == nick)
            return (*uIt).second;
        uIt++;
    }
	return nullptr;
}

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
            std::cout << "test " << _new_socket << std::endl;
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
        int pollReturn = poll(_clients.data(), _clients.size(), 300);
        if (pollReturn == -1) {
            perror("poll() error");
            return BREAK;
        }
        if (pollReturn == 0) {
            return CONTINUE;
        }
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


bool Server::checkAndParseFirst(char *str, pollfd &poll)
{
    if (_users.find(poll.fd) == _users.end()) {
        NormalUser* newUser = new NormalUser(poll);
        _users.insert(std::pair<int, NormalUser *>(poll.fd, newUser));
    }
    std::map<int, NormalUser*>::iterator it = _users.find(poll.fd);
    if (strlen(str) < 4) {
        Utility::sendToClient(poll.fd, ERR_UNKNOWNCOMMAND((*it).second->getPrefix(), str));
        return false;
    }
    std::string buffer(str);
    std::cout << "kvirc:" << str << std::endl;
    buffer = Utility::trimExceptAlphabet(buffer);
    std::vector<std::string> splitSpace = Utility::split(buffer, " ");

    std::cout << std::endl;
    std::cout << "User size: " << _users.size() << std::endl;

    if (splitSpace.empty())
        std::cout << "error\n";
    if (it->second->getAllCheck()) {
        _commands.executeCommand(splitSpace, (*it), *this);
    }
    else {
        if (splitSpace.size() > 1) {
            std::string toUpper = Utility::toUpper(splitSpace[0]);
            if (toUpper == "PASS" || toUpper == "NICK" || toUpper == "USER") {
                _commands.executeCommand(splitSpace, (*it), *this);
            }
            else {
                Utility::sendToClient(poll.fd, ERR_UNKNOWNCOMMAND((*it).second->getPrefix(), str));
            }
        }
        else {
            if (!splitSpace.empty() && Utility::toUpper(splitSpace[0]) == "HELP") {
                _commands.executeCommand(splitSpace, (*it), *this);
            }
            else
                Utility::sendToClient(poll.fd, ERR_UNKNOWNCOMMAND((*it).second->getPrefix(), str));
        }
    }
    return false;
}
