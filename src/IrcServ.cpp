#include "../include/IrcServ.hpp"
#include <arpa/inet.h>

void IrcServ::errorHandle(std::string message, int errorNum)
{
    std::cout << message << std::endl;
    exit(errorNum);
}

IrcServ::IrcServ(int port, std::string passWord)
    : _port(port), _passWord(passWord)
{
    _servFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_servFd == -1) 
        errorHandle("socket error", _servFd);
    if (bind(_servFd, &_servAddr, sizeof(_servAddr)))
        errorHandle("fail bind", -1);
    if (listen(_servFd, 5))
        errorHandle("fail listen", -1);
}

void IrcServ::run()
{
    
}