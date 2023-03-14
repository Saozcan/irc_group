#include "Nick.hpp"


Nick::Nick() : ACommand("NICK"){}

Nick::~Nick() {}

void Nick::execute() {
    std::cout << "Nick command execute" << std::endl;
}