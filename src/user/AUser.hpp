#include <iostream>
#include "poll.h"

class AUser
{
    protected:
        std::string _name;
        std::string _role;
        pollfd      *_poll;

    public:
        AUser();
        AUser(const std::string& name);
        AUser(const std::string& name, const std::string& role);
        AUser(const std::string& name, const std::string& role, const pollfd *poll);
        ~AUser();

        //Setters
        void setName(std::string name);
        void setRole(std::string role);

        //Getters
        std::string getName();
        std::string getRole();
        pollfd& getPoll();
};
