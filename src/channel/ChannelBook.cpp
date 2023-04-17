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
        return nullptr;
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