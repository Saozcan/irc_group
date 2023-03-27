#pragma once

#include <iostream>
#include "poll.h"


class NormalUser
{
    protected:
        std::string _name;
        std::string _role;
        std::string _nick;
        std::string _realName;
        std::string _hostname;
        std::string _serverName;
        std::string _replay;
        pollfd      _poll;
        bool        _pass;
        bool        _allCheck;
        bool        _opCheck;
    public:
        NormalUser();
        NormalUser(pollfd &pollfd);
        ~NormalUser();

        //Setters
        void setName(std::string name);
        void setRole(std::string role);
        void setNick(std::string nick);
        void setPoll(pollfd &poll);
        void setPass(bool boolean);
        void setAllCheck(bool boolean);
        void setRealName(const std::string &realName);
        void setHostname(const std::string &hostName);
        void setServerName(const std::string &serverName);
        void setReplay(const std::string &replay);

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
        const std::string& getReplay() const;
};
