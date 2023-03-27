#include "Channel.hpp"
#include "../utility/Utility.hpp"

Channel::Channel() {}

Channel::Channel(const std::string &name) : _name(name){}

Channel::~Channel() {
//#pragma region FreeChannels
//    std::map<std::string, NormalUser*>::iterator it = _users.begin();
//    while (it != _users.end())
//    {
//        delete (*it).second;
//        it++;
//    }
//    _users.clear();
//#pragma endregion

// Bütün kullanıcılar server da tutulup, takibinde oradan silme işlemi yapılabilir.
// Böylece channel girmemiş kullanıcılarda orada görüleceğinden silme işlemi kesinleşir.
}

void Channel::setChannelName(const std::string &name) {
    _name = name;
}

std::string Channel::getChannelName() {
    return _name;
}

void Channel::AddUser(NormalUser *user) {
    if(_users.empty())
        _operators.insert(std::pair<std::string, NormalUser* >(user->getName(), user));
//    std::string user_name = Utility::strTrim(user->getName());
//    user->setName(user_name);
    std::map<std::string, NormalUser*>::iterator it = _users.find(user->getName());
    if(it == _users.end())
        _users.insert(std::pair<std::string, NormalUser* >(user->getName(), user));
    else
        std::cout << "Duplicate user" << std::endl;
}

void Channel::leaveUser(const std::string& name) {
    _users.erase(name);
}

void Channel::addMode(std::string user) {
    if (_users.empty()) {
        std::cout << "Users map is empty." << std::endl;
        return;
    }
    std::map<std::string, NormalUser*>::iterator it = _users.find(user);
    if(it != _users.end())
        _operators.insert(std::pair<std::string, NormalUser*>((*it).second->getName(), (*it).second));
    else{
        std::cout << "User cannot be found!" << std::endl;
    }
}

void Channel::removeMode(std::string user) {
    std::map<std::string, NormalUser*>::iterator opIt = _operators.find(user);
    if(opIt != _operators.end()) {
        _operators.erase(opIt);
        std::cout << "User " << user << " has been removed from operators." << std::endl;
    }
    else
        std::cout << "User " << user << " is not an operator." << std::endl;
}

bool Channel::checkOperators(std::string user) {

    std::map<std::string, NormalUser*>::iterator it = _operators.find(user);
    if(it != _operators.end())
        return true;
    return false;
}

void Channel::sendMessage(const std::string &from, std::string &message) {

    std::map<std::string, NormalUser*>::iterator it = _users.begin();
    size_t messageLen = strlen(message.c_str());
    for (; it != _users.end(); it++) {
        if (it->second->getName() != from)
            send((*it).second->getPoll().fd, message.c_str(), messageLen, 0);
    }
}

bool Channel::isEmpty() {
    if (this->_users.empty())
        return true;
    return false;
}
