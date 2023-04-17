#pragma once

#include "../ACommand.hpp"

class Quit : public ACommand {
public:
    Quit();
    ~Quit();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
private:
};
