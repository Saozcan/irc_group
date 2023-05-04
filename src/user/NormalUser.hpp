#pragma once

#include <iostream>
#include "poll.h"
#include "vector"
#include "map"
#include "../channel/Channel.hpp"

class Channel;
class NormalUser
{
    protected:
        std::string _name;
        std::string _role;
        std::string _nick;
        std::string _realName;
        std::string _hostname;
        std::string _serverName;
        std::string _prefix;
        std::string _notFinishedText;
        std::map<std::string, Channel*> _channels;
        pollfd      _poll;
        bool        _pass;
        bool        _allCheck;
        bool        _cap;

    public:
        NormalUser();
        NormalUser(pollfd &pollfd);
        ~NormalUser();

        //Setters
        void setUser(std::string name);
        void setRole(std::string role);
        void setNick(std::string nick);
        void setPoll(pollfd &poll);
        void setPass(bool boolean);
        void setAllCheck(bool boolean);
        void setRealName(const std::vector<std::string>& splitArgs);
        void setHostname(const std::string &hostName);
        void setServerName(const std::string &serverName);
        void setPrefix();
        void setCap(bool boolean);
        void addChannel(Channel * channel);
        void notFinishedText(const std::string &text, bool cleanIt);

        //Getters
        std::string getName();
        std::string getRole();
        std::string getNick();
        pollfd& getPoll();
        bool getPass();
        bool getAllCheck();
        std::string getRealName();
        std::string getHostname();
        std::string getServerName();
        const std::string& getPrefix() const;
        bool getCap() const;
        std::string getNotFinishedText() const;
        size_t getNotFinishedTextSize() const;

        //Special
        void leaveChannels();
};
