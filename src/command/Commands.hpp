#include "ACommand.hpp"
/*
Basic Commands
* KICK - ...
• NICK – Give the user a nickname or change the previous one. Your server should
report an error message if a user attempts to use an already-taken nickname.
• USER – Specify the username, hostname, and real name of a user.
• QUIT – End the client session. The server should announce the client’s departure to
all other users sharing the channel with the departing client.
Channel Commands
• JOIN – Start listening to a specific channel. Although the standard IRC protocol
allows a client to join multiple channels simultaneously, your server should restrict a
client to be a member of at most one channel. Joining a new channel should implicitly
cause the client to leave the current channel.
• PART – Depart a specific channel. Though a user may only be in one channel at a
time, PART should still handle multiple arguments. If no such channel exists or it exists
but the user is not currently in that channel, send the appropriate error message.
• LIST – List all existing channels on the local server only. Your server should ignore
parameters and list all channels and the number of users on the local server in each
channel.
3
Advanced Commands
• PRIVMSG – Send messages to users. The target can be either a nickname or a
channel. If the target is a channel, the message will be broadcast to every user on
the specified channel, except the message originator. If the target is a nickname, the
message will be sent only to that user.
• WHO – Query information about clients or channels. In this project, your server only
needs to support querying channels on the local server. It should do an exact match on
the channel name and return the users on that channel.
*/

class ACommand;

class Nick: public ACommand
{
    private:
    public:
        Nick()
        {

        };
        ~Nick()
        {

        };
        void execute()
        {
            std::cout << "nicked user" << std::endl;
        };
};

class Kick: public ACommand
{
    private:
    public:
        Kick()
        {

        };
        ~Kick()
        {

        };
        void execute()
        {
            std::cout << "kicked user" << std::endl;
        };
};

class Join: public ACommand
{
    private:
    public:
        Join()
        {

        };
        ~Join()
        {

        };
        void execute()
        {
            std::cout << "joined user" << std::endl;
        };
};

