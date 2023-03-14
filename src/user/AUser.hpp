#pragma once

#include <iostream>
#include "poll.h"

class AUser
{
    protected:
        std::string _name;
        std::string _role;
        std::string _nick;
        pollfd      *_poll;

    public:
        AUser();
        ~AUser();

        //Setters
        void setName(std::string name);
        void setRole(std::string role);
        void setNick(std::string nick);
        void setPoll(pollfd &poll);

        //Getters
        std::string getName();
        std::string getRole();
        std::string getNick();
        pollfd* getPoll();
};
