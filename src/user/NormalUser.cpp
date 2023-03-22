#include "NormalUser.hpp"

NormalUser::NormalUser() : _name(""), _role("NormalUser"), _nick(""), _pass(true), _allCheck(false) {}

NormalUser::NormalUser(pollfd &pollfd) : _role("NormalUser"), _nick(""), _pass(true), _allCheck(false), _poll(pollfd)  {}


NormalUser::~NormalUser() {}

void NormalUser::setName(std::string name) {
    _name = name;
}

void NormalUser::setNick(std::string nick) {
    _nick = nick;
}

void NormalUser::setRole(std::string role) {
    _role = role;
}

void NormalUser::setPoll(pollfd &poll) {
    _poll = poll;
}

void NormalUser::setPass(bool boolean) {
    _pass = boolean;
}

void NormalUser::setAllCheck(bool boolean) {
    _allCheck = boolean;
}

std::string NormalUser::getName() {
    return _name;
}

std::string NormalUser::getRole() {
    return _role;
}

std::string NormalUser::getNick() {
    return _nick;
}

pollfd& NormalUser::getPoll() {
    return _poll;
}

bool NormalUser::getPass() {
    return _pass;
}

bool NormalUser::getAllCheck() {
    return _allCheck;
}
