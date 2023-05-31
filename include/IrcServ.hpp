#ifndef __IrcServ_hpp__
#define __IrcServ_hpp__

#include "IRC.hpp"

class IrcClient;
class IrcChannel;

class IrcServ
{
public:
    IrcServ(int port, std::string passWord);
    void run();
    ~IrcServ();
private:
    int         _servFd;
    int         _port;
    int         _fdMax;
    int         _fdNum;
    fd_set activeReads, cpyReads;
    fd_set activeWrites, cpyWrites;
    struct sockaddr_in    _servAddr;
    std::string _passWord;
    std::vector <IrcClient *> clients;
    std::vector <IrcChannel *> channels;
    
    IrcServ();
    IrcServ(const IrcServ& copy);
    const IrcServ& operator=(const IrcServ& copy);
    void errorHandle(std::string message, int errorNum);
};

#endif