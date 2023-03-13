#pragma once

#include "src/command/ACommand.hpp"
#include "iostream"

class User : public ACommand {
public:
    User();
    ~User();
    void execute();
private:
};
