#ifndef __IrcCLIENT__
#define __IrcCLIENT__

#include "IRC.hpp"

class IrcServ;
class IrcChannel;

#define MAX_CLIENT_BUFFER_SIZE 1024

class IrcClient {

    private:
    public:
        uint32_t ipAddr;
        uint16_t portNo;
        uint32_t serverIpAddr;
        uint16_t serverPortNo;
        int commFd;
        
        std::vector<IrcChannel *> registredChannels;
        std::vector<IrcChannel *> operatorChannels;
        IrcClient(uint32_t ipAddr, uint16_t portNo);
        void Display();
        
} ;


#endif