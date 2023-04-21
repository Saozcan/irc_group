//
// Created by ebudak on 3/10/23.
//

#ifndef IRC_GROUP_JOIN_HPP
#define IRC_GROUP_JOIN_HPP

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

#endif //IRC_GROUP_JOIN_HPP
