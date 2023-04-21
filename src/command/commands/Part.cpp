#include "Part.hpp"
#include "../../utility/Utility.hpp"

class NormalUser;

Part::Part() : ACommand("PART") {}

Part::~Part() {}

void
Part::execute(const std::vector<std::string> &splitArgs, std::pair<const int, NormalUser *> &user, Server &server) {
    if (splitArgs.size() < 2) {
        std::string errMessage = ERR_NEEDMOREPARAMS(user.second->getNick(), splitArgs[0]);
        Utility::sendToClient(user.first, errMessage);
        return;
    }
    std::string channelName = Utility::strTrim(splitArgs[1]);
    Channel *channelTmp = server._channels.getChannel(channelName);
    if (channelTmp == nullptr) {
        std::string errMessage = ERR_NOSUCHCHANNEL(user.second->getNick(), channelName);
        return ;
    }
    NormalUser* userTmp = channelTmp->getUser(user.second->getNick());
    if (userTmp == nullptr) {
        std::string errMessage = ERR_NOTONCHANNEL(user.second->getNick(), channelName);
        Utility::sendToClient(user.first, errMessage);
        return ;
    }
    if (channelTmp->getNbOperators() == 1 && channelTmp->getNbUsers() > 1) {
        channelTmp->addModeAll();
    }
    std::string messageToChannel = user.second->getPrefix() + " " + splitArgs[0] + " " + splitArgs[1] + "\r\n";
    channelTmp->sendMessage(user.second->getNick(), messageToChannel, false);
    channelTmp->leaveUser(user.second->getNick());
}
