#pragma once

#include "../ACommand.hpp"

class Help : public ACommand {
public:
    Help();
    ~Help();
    void execute(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, Server& server);
private:
};
