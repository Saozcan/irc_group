#include "ChannelBook.hpp"
#include "../utility/Utility.hpp"

ChannelBook::ChannelBook() {}

ChannelBook::~ChannelBook() {
    std::map<std::string, Channel*>::iterator it = _channels.begin();
    while (it != _channels.end())
    {
        delete (*it).second;
        it++;
    }
    _channels.clear();
}

Channel* ChannelBook::createChannel(std::string& channelName){
    std::string channel = Utility::strTrim(channelName);
    std::map<std::string, Channel*>::iterator it = _channels.find(channel);
    Channel * my_channel;
    if(it == _channels.end()){
        my_channel = new Channel(channel);
        _channels.insert(std::pair<std::string, Channel *>(channel,my_channel));
        return my_channel;
    }
    return (*it).second;
}

Channel* ChannelBook::getChannel(const std::string& channelName) {
    std::map<std::string, Channel*>::iterator it = _channels.find(Utility
            ::strTrim(channelName));
    if (it != _channels.end())
        return (*it).second;
    else
        return NULL;
}


bool ChannelBook::removeChannel(std::string& channelName) {
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it != _channels.end()) {
        _channels.erase(it);
        return true;
    }
    else
        return false;
}

void ChannelBook::quitUser(const std::string &nick) {
    std::map<std::string, Channel*>::iterator it = _channels.begin();
    while (it != _channels.end())
    {
        (*it).second->leaveUser(nick);
        it++;
    }
}

void ChannelBook::writeChannels() const {
    std::map<std::string, Channel*>::const_iterator it = _channels.begin();
    while (it != _channels.end())
    {
        std::cout << (*it).first << std::endl;
        (*it).second->writeUsers();
        it++;
    }
}
