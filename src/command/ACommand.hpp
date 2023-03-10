#include <iostream>

class ACommand
{
    private:
        std::string _name;
        
    public:
        ACommand();
        ACommand(const std::string& name);
        virtual void execute() = 0;
        virtual ~ACommand();
        void setName(const std::string& name);
        std::string getName();
};
