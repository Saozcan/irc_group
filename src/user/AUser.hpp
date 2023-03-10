#include <iostream>

class AUser
{
    protected:
        std::string _name;
        std::string _role;

    public:
        AUser();
        AUser(const std::string& name);
        AUser(const std::string& name, const std::string& role);
        ~AUser();

        //Setters
        void setName(std::string name);
        void setRole(std::string role);

        //Getters
        std::string getName();
        std::string getRole();
};
