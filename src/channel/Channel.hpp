#include <iostream>
#include <vector>
#include <map>

#include "../../irc.hpp"

/**
 * Mesajlar tutulabilir.
 */

class Channel
{
    private:
        std::map<std::string, AUser*> _users;
        std::string _name;

    public:
        Channel();
        Channel(const std::string &name);
        ~Channel();

        void setChannelName(const std::string &name);
        std::string getChannelName();

        void AddUser(AUser *user);
        void LeaveUser(AUser *user);
};
