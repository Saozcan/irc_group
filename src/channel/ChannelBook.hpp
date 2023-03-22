#pragma once

#include "iostream"
#include "map"

#include "Channel.hpp"

class ChannelBook {

public:
    ChannelBook();
    ~ChannelBook();
    Channel* createChannel(std::string& channelName);
    Channel* getChannel(std::string& channelName);
    bool removeChannel(std::string& channelName);

private:
    std::map<std::string, Channel*> _channels;
};


