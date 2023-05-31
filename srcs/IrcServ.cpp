#include "../include/IRC.hpp"
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024 
char buf[BUF_SIZE];


IrcServ::IrcServ(int port, std::string passWord)
    : _port(port), _passWord(passWord)
{
    _servFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&_servAddr, 0, sizeof(_servAddr));
    _servAddr.sin_family = AF_INET;
    _servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    _servAddr.sin_port=htons(port);
// setsockopt 추가
    if (_servFd == -1) 
        ErrorHandle::errorHandle("socket error", _servFd);
    if (bind(_servFd, (struct sockaddr*)&_servAddr, sizeof(_servAddr)))
        ErrorHandle::errorHandle("fail bind", -1);
    if (listen(_servFd, 5))
        ErrorHandle::errorHandle("fail listen", -1);

    FD_ZERO(&_activeReads);
    FD_ZERO(&_activeWrites);
}


void IrcServ::run()
{

    int rcv_bytes;
    IrcClient *ircClient, *nextIrcClient;
    struct sockaddr_in client_addr;
    std::list<IrcClient *>::iterator it;
    socklen_t addr_len = sizeof(client_addr);

    while(true) {
        //sleep(3);
        FD_SET(_servFd, &_activeReads);
        FD_SET(_servFd, &_activeWrites);
        _fdMax = _servFd > GetMaxFd() ? _servFd : GetMaxFd() ;
        this->CopyClientFDtoFDSet(&this->_cpyReads);
        _activeReads = _cpyReads;
        printf("_servFd is %d port is %d  fdMax is %d \n", _servFd, _port, _fdMax);
        select(_fdMax+1 , &this->_activeReads, NULL, NULL, NULL);
        printf("after select\n");

        /* getNewConnection*/
         if (FD_ISSET(_servFd, &this->_activeReads)) 
         {
            printf("newconnection detected\n");
            int comm_socket_fd;
            comm_socket_fd =  accept (_servFd,
                                                     (struct sockaddr *)&client_addr, &addr_len);
            IrcClient *ircClient = new IrcClient();
            ircClient->_commFd = comm_socket_fd;
            printf("ircClient_commfd in newconnect : %d  comm_socket_fd : %d\n", ircClient->_commFd, comm_socket_fd);
            ircClient->_ipAddr = htonl(client_addr.sin_addr.s_addr);
            ircClient->_portNo = htons(client_addr.sin_port);
            FD_SET(ircClient->_commFd, &_cpyReads);
            AddClients(ircClient);
         }        
        /* Iterate so that we can delete the current element while traversing */
        for (it = this->_clients.begin(), ircClient = *it;
             it != this->_clients.end();
             ircClient = nextIrcClient)
             {

                nextIrcClient = *(++it);
            printf("after for it\n");


            printf("ircclient_fd is %d\n", ircClient->getCommFd());
            if (FD_ISSET(ircClient->getCommFd(), &this->_activeReads)) 
            {
                    printf("recv in commfd : %d\n", ircClient->getCommFd());
                    
                    rcv_bytes = recvfrom(ircClient->getCommFd(),
                            ircClient->recv_buffer,
                            MAX_CLIENT_BUFFER_SIZE,
                            0, 
                            (struct sockaddr *)&client_addr, &addr_len);

                    if (rcv_bytes == 0 || rcv_bytes < 0) {
                        /* Remove FD from fd_set otherwise, select will go in infinite loop*/
                        FD_CLR(ircClient->getCommFd(), &this->_cpyReads);
                        this->RemoveClients(ircClient);
                        _fdMax = GetMaxFd();
                    }
                    else {

                        /*handle recv message*/
                    printf("MAX_CLIENT_BUFFER_SIZE : %d\n", MAX_CLIENT_BUFFER_SIZE);
                    printf ("%s() Bytes recvd : %d msg : %s\n",  __FUNCTION__, MAX_CLIENT_BUFFER_SIZE, ircClient->recv_buffer);
                    //write(1, buf, rcv_bytes);
                    //write(1, "\n", 1);
                    }
            
            std::cout << "IrcServ::run() while loop" << std::endl;
            //break;
            }
            
        }
    }
}

IrcServ::~IrcServ() {};

int IrcServ::GetMaxFd() 
{

    int max_fd_lcl = 0;

    IrcClient *ircClient;
    std::list<IrcClient *>::iterator it;

    for (it = this->_clients.begin(); it != this->_clients.end(); ++it) {

        ircClient = *it;
        int commFd = ircClient->getCommFd();
        if (commFd > max_fd_lcl ) {
            max_fd_lcl = commFd;
        }
    }
    return max_fd_lcl;
}


void IrcServ::CopyClientFDtoFDSet(fd_set *fdset) {

    IrcClient *ircClient;
    std::list<IrcClient *>::iterator it;


    for (it = this->_clients.begin(); 
            it != this->_clients.end();
            ++it) {

        ircClient = *it;
        FD_SET(ircClient->getCommFd(), fdset);
    }
}

void IrcServ::RemoveClients(IrcClient *ircClient) {

    this->_clients.remove(ircClient);
    //ircClient객체를 삭제해야하니까 메모리관리 추가??
}

void IrcServ::AddClients(IrcClient *ircClient){

     this->_clients.push_back(ircClient);
}
