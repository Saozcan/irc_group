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
}

void Channel::LeaveUser(NormalUser *user) {
    _users.erase(user->getName());
}
