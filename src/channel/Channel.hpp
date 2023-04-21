#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "../user/NormalUser.hpp"

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

        void addUser(NormalUser *user);
        void leaveUser(const std::string& name);
        void addMode(const std::string& user);
        void addModeAll();
        void removeMode(const std::string& user);
        bool checkOperators(const std::string& user);
        void sendMessage(const std::string& from, std::string& message, bool isMessage);
        bool isEmpty();
        void sendMode(int fd, const std::string& mode) const;
        NormalUser* getUser(const std::string &nick) const;
        void writeUsers() const;
        std::string getUsers () const;
        std::string getOperators () const;

        //sizes
        size_t getNbUsers() const;
        size_t getNbOperators() const;

        //irc numerics
        void irc315(int fd);
        void irc353(int fd, bool isAll);
        void irc366(int fd, bool isAll);
        void irc352(int fd);
};
