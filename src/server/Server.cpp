#include "Server.hpp"

enum loop {
    BREAK,
    CONTINUE,
};

Server::Server() {
    _hostName = "127.0.0.1";
    _serverName = "ircserv";
    _port = 8050;
    _pass = "123abc";
    _addrlen = sizeof(_address);
}

Server::Server(std::string const &hostName, std::string const &serverName, unsigned short port)
{
    _hostName = hostName;
    _serverName = serverName;
    _port = port;
    _addrlen = sizeof(_address);
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
    std::vector<pollfd> _clientNotActives;
    std::vector<int> check;

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
            _clientNotActives.push_back(tmp);
            check.push_back(0);
        }
        listenNotActiveClients(_clients, _clientNotActives, check, buffer);
        if (listenClients(_clients, buffer) == BREAK)
            break;
        else
            continue;
    }
}

int Server::listenNotActiveClients(std::vector<pollfd> &_clients, std::vector<pollfd>& notActiveClients, std::vector<int> &check, char* buffer) {
    if (!notActiveClients.empty()) {
        int pollReturn = poll(notActiveClients.data(), notActiveClients.size(), 1000);
        if (pollReturn == -1) {
            perror("poll() error");
            return BREAK;
        }
        if (pollReturn == 0) {
            return CONTINUE;
        } // -1 hiç bekleme süresi koymaz
        std::cout << "client size: "<< notActiveClients.size() << std::endl;
        std::vector<int>::iterator checkIt = check.begin();
        for (std::vector<pollfd>::iterator it = notActiveClients.begin(); it < notActiveClients.end(); it++) {
            checkIt++;
            int requestCount = 0;
            if ((*it).revents & POLLIN && *checkIt == 0) {
                int valread;
                while ((valread = recv((*it).fd, buffer, 1024, MSG_DONTWAIT)) > 0) { //MSG_DONT... non blcok için
                    buffer[valread] = '\0';
                    if (checkAndParseFirst(buffer, (*it), (*checkIt))) {
                        _clients.push_back(*it);
                        *checkIt = 1;
                        std::cout << "New client added" << std::endl;
                    }
                    memset(buffer, 0, strlen(buffer));
                }
                requestCount++;
                if (valread == 0) {
                    (*it).fd = -1;
                    (*it).events = 0;
                }
            }
            checkIt = check.begin();
            for (std::vector<pollfd>::iterator it = notActiveClients.begin(); it < notActiveClients.end(); ) {
                checkIt++;
                if ((*it).fd == -1) {
                    it = notActiveClients.erase(it);
                    check.erase(checkIt);
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
                    if (checkAndParse(*this, (*it), buffer)) {
                        std::cout << buffer << std::endl;
                    } else {
                    }
                    memset(buffer, 0, strlen(buffer));
                }
                requestCount++;
                if (valread == 0) {
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
    _channels.insert(std::pair<std::string, Channel*>(channel->getChannelName(), channel));
}

void Server::removeChannel(Channel *channel) {
    _channels.erase(channel->getChannelName());
}

void Server::addUser(AUser *user) {
    _users.insert(std::pair<std::string, AUser*>(user->getName(), user));
}

void Server::removeUser(AUser *user) {
    _users.erase(user->getName());
}

bool Server::checkAndParseFirst(char *str, pollfd &poll, int& checkIt) {
    std::string buffer(str);
    std::vector<std::string> splitSpace = Server::split(buffer, " ");
    if (checkIt >= 1 || Server::toUpper(splitSpace[0]) == "PASS") {
        checkIt == 0 ? checkIt = 1 : checkIt = checkIt;
        if (checkIt >= 3 || strcmp(splitSpace[1].c_str(), _pass.c_str()) != 0) {
            send(poll.fd, "Please enter valid USER command.", strlen("Please enter valid USER command."), 0);
            return true;
        }
        else
            send(poll.fd, "Please enter correct password.", strlen("Please enter correct password."), 0);
    } else {
        send(poll.fd, "Please enter valid PASS command.", strlen("Please enter valid PASS command."), 0);
    }
    return false;
}


//Statics
bool Server::checkAndParse(Server &server, pollfd &poll, char* str) {
    std::string buffer(str);
    std::vector<std::string> splitSpace = Server::split(buffer, " ");
    if (Server::toUpper(splitSpace[0]) == "PASS")
        return true;

    return false;
}

std::vector<std::string> Server::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    if (end > str.length()) {
        tokens.push_back(str.substr(start, str.length()));
        return tokens;
    }
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    if (start != str.length()) {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}

std::string& Server::toUpper(std::string &str) {
    std::string::iterator it = str.begin();
    while (it++ != str.end()) {
        toupper((*it));
    }
    return str;
}
