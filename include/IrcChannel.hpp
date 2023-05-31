#ifndef __IrcCHANNEL__
#define __IrcCHANNEL__

#include "IRC.hpp"

class IrcServ;
class IrcClient;

#define MAX_CLIENT_BUFFER_SIZE 1024

class IrcChannel {

    private:
    public:
        std::string channelName;
        std::string channelTopic;

        
        std::vector<IrcClient *> registredClients;
        std::vector<IrcClient *> operatorClients;
        IrcChannel(std::string channelName);
        void Display();
        
} ;


#endif