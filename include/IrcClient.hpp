#ifndef __IrcCLIENT__
#define __IrcCLIENT__

#include "IRC.hpp"

class IrcServ;
class IrcChannel;

#define MAX_CLIENT_BUFFER_SIZE 1024

class IrcClient {
    public:
        IrcClient(uint32_t ipAddr, uint16_t portNo);
        void Display();

    private:
        uint32_t _ipAddr;
        uint16_t _portNo;
        uint32_t _serverIpAddr;
        uint16_t _serverPortNo;
        int      _commFd;
        
        std::vector<IrcChannel> _registredChannels;
        std::vector<IrcChannel> _operatorChannels;        
} ;


#endif