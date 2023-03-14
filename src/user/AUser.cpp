#include "AUser.hpp"

AUser::AUser() : _name(""), _role("user"), _nick("") {}

AUser::~AUser() {}

void AUser::setName(std::string name) {
    _name = name;
}

void AUser::setNick(std::string nick) {
    _nick = nick;
}

void AUser::setRole(std::string role) {
    _role = role;
}

void AUser::setPoll(pollfd &poll) {
    _poll = &poll;
}

std::string AUser::getName() {
    return _name;
}

std::string AUser::getRole() {
    return _role;
}

std::string AUser::getNick() {
    return _nick;
}

pollfd* AUser::getPoll() {
    return _poll;
}
