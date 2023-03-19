#include "Channel.hpp"

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
    std::cout << user->getName() << this->getChannelName() << std::endl;
    _users.insert(std::pair<std::string, NormalUser* >(user->getName(), user));
    std::map<std::string, NormalUser*>::iterator it2 = _users.begin();
    for (; it2 != _users.end() ; it2++) {
        std::cout<<"userss:: " << (it2)->second->getName() << std::endl;
    }
}

void Channel::LeaveUser(NormalUser *user) {
    _users.erase(user->getName());
}

void Channel::addMode(std::string user) {
    if (_users.empty()) {
        std::cout << "users map is empty." << std::endl;
        return;
    }
    std::map<std::string, NormalUser*>::iterator it = _users.find(user);
    std::map<std::string, NormalUser*>::iterator it2 = _users.begin();

    for (; it2 != _users.end() ; it2) {
        std::cout<<"userss2222:: " << (*it2).second->getName() << std::endl;
         it2++;
        break;
    }
    if(it != _users.end())
        it->second->setOpCheck(true);
//        _operators.insert(std::pair<std::string, NormalUser*>((*it).second->getName(), (*it).second));
    else{
        std::cout << "User cannot be found!" << std::endl;
    }
}
