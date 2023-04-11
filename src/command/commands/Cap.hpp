#pragma once

#include "../ACommand.hpp"

class Cap : public ACommand {
public:
    Cap();
    ~Cap();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
private:
};
