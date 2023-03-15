#pragma once

#include <iostream>
#include "poll.h"

class NormalUser
{
    protected:
        std::string _name;
        std::string _role;
        std::string _nick;
        pollfd      *_poll;
        bool        _pass;
        bool        _allCheck;

    public:
        NormalUser();
        ~NormalUser();

        //Setters
        void setName(std::string name);
        void setRole(std::string role);
        void setNick(std::string nick);
        void setPoll(pollfd &poll);
        void setPass(bool boolean);
        void setAllCheck(bool boolean);

        //Getters
        std::string getName();
        std::string getRole();
        std::string getNick();
        pollfd* getPoll();
        bool getPass();
        bool getAllCheck();
};
