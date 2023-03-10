#include "iostream"
#include "src/server/Server.hpp"

int main(int argc, char const *argv[])
{
    Server server;

    std::cout << server.getServerName() << std::endl;
    /* code */
    return 0;
}
