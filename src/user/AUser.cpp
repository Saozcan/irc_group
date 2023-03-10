#include "AUser.hpp"

AUser::AUser() : _name("Default"), _role("user") {}

AUser::AUser(const std::string &name) : _name(name), _role("user"){}

AUser::AUser(const std::string &name, const std::string &role) : _name(name), _role(role) {}

AUser::~AUser() {}

void AUser::setName(std::string name) {
    _name = name;
}

void AUser::setRole(std::string role) {
    _role = role;
}

std::string AUser::getName() {
    return _name;
}

std::string AUser::getRole() {
    return _role;
}
