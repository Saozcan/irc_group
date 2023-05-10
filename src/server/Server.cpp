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
    _port = port;
    _pass = password;
    _addrlen = sizeof(_address);
    _serverName = "ircserv";
};

Server::~Server() {
    std::map<int, NormalUser*>::iterator uIt = _users.begin();
    while (uIt != _users.end())
    {
        delete (*uIt).second;
        uIt++;
    }
    _users.clear();
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
	return NULL;
}

void Server::listenServer() {
    this->createSocketFd();
    this->acceptClient();
}

void Server::createSocketFd() {
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw std::runtime_error("Error: Socket failed");
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);
    const int enable = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("Error: Socket failed");
    if (bind(_server_fd, (sockaddr*)&_address, sizeof(_address)) < 0) {
        throw std::runtime_error("Error: Bind failed");
    }
    if (listen(_server_fd, 3) < 0) {
        throw std::runtime_error("Error: Listen failed");
    }
}

void Server::acceptClient() {
    std::vector<pollfd> _clients;

    char buffer[1024] = {0};
    fcntl(_server_fd, F_SETFL, O_NONBLOCK);
    while (true) {
        while (true) {
            if ((_new_socket = accept(_server_fd, (sockaddr*)&_address, (socklen_t*)&_addrlen)) < 0) {
                break;
            }
            struct pollfd tmp;
            tmp.fd = _new_socket;
            tmp.events = POLLIN;
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
        int pollReturn = poll(_clients.data(), _clients.size(), 50);
        if (pollReturn == -1) {
            std::cerr << "poll() error" << std::endl;
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
                    close((*it).fd);
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


bool Server::checkAndParseFirst(const char *str, pollfd &poll)
{
    if (_users.find(poll.fd) == _users.end()) {
        NormalUser* newUser = new NormalUser(poll);
        _users.insert(std::pair<int, NormalUser *>(poll.fd, newUser));
    }
    if (str[0] == '\n' || str[0] == '\r')
        return false;
    std::map<int, NormalUser*>::iterator it = _users.find(poll.fd);
    std::string buffer(str);
    if (buffer[buffer.size() - 1] != '\n') {
        it->second->notFinishedText(str, false);
        return false;
    }
    else {
        if (it->second->getNotFinishedTextSize() > 0) {
            std::string notFinishedText = it->second->getNotFinishedText() + buffer;
            it->second->notFinishedText("", true);
            buffer = notFinishedText;
        }
    }
    std::cout << "kvirc:" << str << std::endl;
    buffer = Utility::trimExceptAlphabet(buffer);
    std::vector<std::string> splitSpace = Utility::split(buffer, " ");
    std::cout << "fd: " << poll.fd << " " << splitSpace[0] << std::endl;
    if (splitSpace.empty())
        return false;
    if (it->second->getAllCheck()) {
        _commands.executeCommand(splitSpace, (*it), *this);
    }
    else {
        std::string toUpper = Utility::toUpper(splitSpace[0]);
        if (toUpper == "PASS" || toUpper == "NICK" || toUpper == "USER" || toUpper == "HELP") {
            _commands.executeCommand(splitSpace, (*it), *this);
        }
        else {
            Utility::sendToClient(poll.fd, ERR_NOTREGISTERED((*it).second->getNick()));
            std::string message = "First finish your profile\nPASS <pass>\nNICK <nick name>\nUSER <username> <hostname> <servername> <realname> \n";
            Utility::sendToClient(poll.fd, message);
        }
    }
    return false;
}
