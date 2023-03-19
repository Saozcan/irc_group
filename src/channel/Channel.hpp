#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "../user/NormalUser.hpp"

/**
 * Mesajlar tutulabilir.
 */

class Channel
{
    private:
        std::map<std::string, NormalUser*> _users;
        std::map<std::string, NormalUser*> _operators;
        std::pair<std::string, NormalUser*> _admin;

        std::string _name;

    public:
        Channel();
        Channel(const std::string &name);
        ~Channel();

        void setChannelName(const std::string &name);
        std::string getChannelName();

        void AddUser(NormalUser *user);
        void LeaveUser(NormalUser *user);
        void addMode(std::string user);
        void setAdmin();
};
