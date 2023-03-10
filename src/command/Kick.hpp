//
// Created by ebudak on 3/10/23.
//

#ifndef IRC_GROUP_KICK_HPP
#define IRC_GROUP_KICK_HPP


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

#endif //IRC_GROUP_KICK_HPP
