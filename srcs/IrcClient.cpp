#include <arpa/inet.h>
#include "../include/IrcClient.hpp"

IrcClient::IrcClient(uint32_t ipAddr, uint16_t portNo) {

    this->_ipAddr = ipAddr;
    this->_portNo = portNo;
}

void
IrcClient::Display() {

    /*
    char ipAddrStr1[16];
    char ipAddrStr2[16];
    
    printf ("Irc Client : [%s , %d] connected to [%s, %d]\n", 
        network_convert_ip_n_to_p(this->ip_addr, ip_addr_str1),
        (this->port_no),
        network_convert_ip_n_to_p(this->server_ip_addr, ip_addr_str2),
        (this->server_port_no)
        );
    */
}

