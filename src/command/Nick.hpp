//
// Created by ebudak on 3/10/23.
//

#ifndef IRC_GROUP_NICK_HPP
#define IRC_GROUP_NICK_HPP


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



#endif //IRC_GROUP_NICK_HPP
