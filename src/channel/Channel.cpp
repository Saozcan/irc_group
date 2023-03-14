#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(const std::string &name) : _name(name){}

Channel::~Channel() {
//#pragma region FreeChannels
//    std::map<std::string, AUser*>::iterator it = _users.begin();
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

void Channel::AddUser(AUser *user) {
    _users.insert(std::pair<std::string, AUser* >(user->getName(), user));
}

void Channel::LeaveUser(AUser *user) {
    _users.erase(user->getName());
}
