#pragma once

#include "iostream"
#include "map"

#include "Channel.hpp"

class ChannelBook {

public:
    ChannelBook();
    ~ChannelBook();
    Channel* createChannel(std::string& channelName);
    Channel* getChannel(const std::string& channelName);
    bool removeChannel(std::string& channelName);
    void quitUser(const std::string& nick);

private:
    std::map<std::string, Channel*> _channels;
};


