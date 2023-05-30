#ifndef __IrcServ_hpp__
#define __IrcServ_hpp__

#include "IRC.hpp"

class User;
class Channel;

class IrcServ
{
public:
    IrcServ(int port, std::string passWord);
    void run();
    ~IrcServ();
private:
    int         _servFd;
    int         _port;
    sockaddr    _servAddr;
    std::string _passWord;
    std::vector <User> users;
    std::vector <Channel> Channels;
    
    IrcServ();
    IrcServ(const IrcServ& copy);
    const IrcServ& operator=(const IrcServ& copy);
    void errorHandle(std::string message, int errorNum);
};

#endif