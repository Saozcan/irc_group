#include "Channel.hpp"
#include "../utility/Utility.hpp"

Channel::Channel() {}

Channel::Channel(const std::string &name) : _name(name){}

Channel::~Channel() {}

void Channel::setChannelName(const std::string &name) {
    _name = name;
}

void Channel::addUser(NormalUser *user) {
    if(_users.empty()) {
        _operators.insert(std::pair<std::string, NormalUser *>(user->getNick(), user));
        _users.insert(std::pair<std::string, NormalUser* >(user->getNick(), user));
        return ;
    }
    std::map<std::string, NormalUser*>::iterator it = _users.find(user->getNick());
    if(it == _users.end())
        _users.insert(std::pair<std::string, NormalUser* >(user->getNick(), user));
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
        if (it->first == from)
            continue;
        Utility::sendToClient((*it).second->getPoll().fd, message);
    }
}

void Channel::irc366() {
    std::string message = ":ircserv 366 #" + _name + " :";
    std::map<std::string, NormalUser*>::iterator it = _users.begin();
    for (; it != _users.end(); it++) {
        message += it->first + " ";
    }
    std::cout << message << std::endl;
    message += ":End of /NAMES list\r\n";
    for (it = _users.begin(); it != _users.end(); it++)
        Utility::sendToClient(it->second->getPoll().fd, message);
}

bool Channel::isEmpty() {
    if (this->_users.empty())
        return true;
    return false;
}

NormalUser *Channel::getUser(const std::string &nick) const {
    std::map<std::string, NormalUser*>::const_iterator it = _users.find(nick);
    if (it != _users.end())
        return it->second;
    return nullptr;
}

void Channel::writeUsers() const {
    std::map<std::string, NormalUser*>::const_iterator it = _users.begin();
    for (; it != _users.end(); it++) {
        std::cout << "User: " << it->first << std::endl;
    }
}
