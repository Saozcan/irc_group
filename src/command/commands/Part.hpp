#pragma once

#include "../ACommand.hpp"

class Part : public ACommand {
public:
    Part();
    ~Part();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
private:
};
