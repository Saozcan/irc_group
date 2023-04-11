#include "Channel.hpp"
#include "../utility/Utility.hpp"

Channel::Channel() {}

Channel::Channel(const std::string &name) : _name(name){}

Channel::~Channel() {}

void Channel::setChannelName(const std::string &name) {
    _name = name;
}

std::string Channel::getChannelName() {
    return _name;
}

void Channel::addUser(NormalUser *user) {
    if(_users.empty())
        _operators.insert(std::pair<std::string, NormalUser* >(user->getNick(), user));
    std::map<std::string, NormalUser*>::iterator it = _users.find(user->getName());
    if(it == _users.end())
        _users.insert(std::pair<std::string, NormalUser* >(user->getNick(), user));
    else
        std::cout << "Duplicate user" << std::endl;
}

void Channel::leaveUser(const std::string& name) {
    _users.erase(name);
}

void Channel::addMode(const std::string& user) {
    std::map<std::string, NormalUser*>::iterator it = _users.find(user);
    if(it != _users.end())
        _operators.insert(std::pair<std::string, NormalUser*>((*it).second->getNick(), (*it).second));
    else{
        std::cout << "User cannot be found!" << std::endl;
    }
}

void Channel::removeMode(const std::string& user) {
    std::map<std::string, NormalUser*>::iterator opIt = _operators.find(user);
    if(opIt != _operators.end()) {
        _operators.erase(opIt);
        std::cout << "User " << user << " has been removed from operators." << std::endl;
    }
    else
        std::cout << "User " << user << " is not an operator." << std::endl;
}

bool Channel::checkOperators(const std::string& user) {
    std::map<std::string, NormalUser*>::iterator it = _operators.find(user);
    if(it != _operators.end())
        return true;
    return false;
}

void Channel::sendMessage(const std::string &from, std::string &message) {
    std::map<std::string, NormalUser*>::iterator it = _users.begin();
    for (; it != _users.end(); it++) {
        if (it->second->getNick() != from)
            Utility::sendToClient((*it).second->getPoll().fd, message);
    }
}

void Channel::irc366(int fd) {
    std::string message = "ircserv 366 " + _name + " :";
    std::map<std::string, NormalUser*>::iterator it = _users.begin();
    for (; it != _users.end(); it++) {
        message += it->first + " ";
    }
    message += ":End of /NAMES list\r\n";
    Utility::sendToClient(fd, message);
}

bool Channel::isEmpty() {
    if (this->_users.empty())
        return true;
    return false;
}

unsigned int Channel::getUserSize() {
    return _users.size();
}
