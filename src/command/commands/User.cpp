#include "User.hpp"

User::User() : ACommand("USER"){}

User::~User() {}

void User::execute() {
    std::cout << "User command execute" << std::endl;
}