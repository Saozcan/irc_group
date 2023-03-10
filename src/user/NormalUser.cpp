#include "NormalUser.hpp"

NormalUser::NormalUser() : AUser(){}

NormalUser::NormalUser(const std::string& name) : AUser(name, "user"){}

NormalUser::~NormalUser() {}

