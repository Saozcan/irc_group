#pragma once

#include "../ACommand.hpp"

class User : public ACommand {
public:
    User();
    ~User();
    void execute();
private:
};