#include "Cap.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Cap::Cap() : ACommand("CAP") {}

Cap::~Cap() {}

void
Cap::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    (void)splitArgs;
    (void)server;
	std::cout << "Cap command activated \n" ;
    if (user.second->getCap() == false) {
		Utility::sendToClient(user.first, "CAP * LS :multi-prefix sasl\r\n");
		user.second->setCap(true);
	}
	else {
		user.second->getPoll().events = 0;
		Utility::sendToClient(user.first, "CAP * ACK :multi-prefix\r\n");
		user.second->setCap(false);
	}
}
