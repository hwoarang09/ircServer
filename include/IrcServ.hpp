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

    fd_set      _activeReads;
    fd_set      _activeWrites;
    fd_set      _cpyReads;
    fd_set      _cpyWrites;

    struct sockaddr_in          _servAddr;
    std::string                 _passWord;
    std::vector <IrcClient>     _clients;
    std::vector <IrcChannel>    _channels;
    
    IrcServ();
    IrcServ(const IrcServ& copy);
    const IrcServ& operator=(const IrcServ& copy);
};

#endif