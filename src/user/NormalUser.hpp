#include "AUser.hpp"

class NormalUser: public AUser
{
    private:
    public:
        NormalUser();
        NormalUser(const std::string& name);
        ~NormalUser();
};
