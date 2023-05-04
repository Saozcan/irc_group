#include "NormalUser.hpp"

NormalUser::NormalUser() :
_name(""), _role("NormalUser"), _nick(""), _notFinishedText(""), _pass(false), _allCheck(false) {}

NormalUser::NormalUser(pollfd &pollfd):
_role("NormalUser"), _nick(""), _notFinishedText(""), _poll(pollfd) , _pass(false) , _allCheck(false) {}

NormalUser::~NormalUser() {}

void NormalUser::setUser(std::string name) {
    _name = name;
}

void NormalUser::setNick(std::string nick) {
    _nick = nick;
}

void NormalUser::setRole(std::string role) {
    _role = role;
}

void NormalUser::setPoll(pollfd &poll) {
    _poll = poll;
}

void NormalUser::setPass(bool boolean) {
    _pass = boolean;
}

void NormalUser::setAllCheck(bool boolean) {
    _allCheck = boolean;
}

std::string NormalUser::getName() {
    return _name;
}

std::string NormalUser::getRole() {
    return _role;
}

std::string NormalUser::getNick() {
    return _nick;
}

pollfd& NormalUser::getPoll() {
    return _poll;
}

bool NormalUser::getPass() {
    return _pass;
}

bool NormalUser::getAllCheck() {
    return _allCheck;
}

void NormalUser::setRealName(const std::vector<std::string>& splitArgs) {
    std::string realName = "";
    for (size_t i = 3; i < splitArgs.size(); i++) {
        realName += splitArgs[i];
        if (i != splitArgs.size() - 1)
            realName += " ";
    }
    _realName = realName;
}

void NormalUser::setHostname(const std::string &hostName) {
    _hostname = hostName;
}

void NormalUser::setServerName(const std::string &serverName) {
    _serverName = serverName;
}

std::string NormalUser::getRealName() {
    return _realName;
}

std::string NormalUser::getHostname() {
    return _hostname;
}

std::string NormalUser::getServerName() {
    return _serverName;
}

void NormalUser::setPrefix() {
    _prefix = ":" + _nick + "!" + _name + "@" + _hostname;
}

void NormalUser::setCap(bool boolean){
    _cap = boolean;
}

const std::string &NormalUser::getPrefix() const {
    return _prefix;
}

bool NormalUser::getCap() const{
	return _cap;
}

void NormalUser::addChannel(Channel *channel) {
    _channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
}

void NormalUser::leaveChannels() {
    std::map<std::string, Channel*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++) {
        std::string messageToChannel = _prefix + " " + "PART" + " #" + it->first + "\r\n";
        it->second->sendMessage(_nick, messageToChannel, false);
        it->second->leaveUser(_nick);
        if ((*it).second->getNbOperators() == 0 && (*it).second->getNbUsers())
            it->second->addModeAll();
    }
    _channels.clear();
}

void NormalUser::notFinishedText(const std::string &text, bool cleanIt) {
    if (cleanIt)
        _notFinishedText = "";
    _notFinishedText += text;
}

std::string NormalUser::getNotFinishedText() const {
    return _notFinishedText;
}

size_t NormalUser::getNotFinishedTextSize() const {
    return _notFinishedText.size();
}
