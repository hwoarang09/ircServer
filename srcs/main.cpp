#include "../include/IRC.hpp"
#include "../include/IrcServ.hpp"
#include "../include/IrcClient.hpp"
int main(int argc, char **argv)
{
    (void)argc;
    int port;
    port = atoi(argv[1]);
    printf("port : %d\n", port);
    printf("ip : %d\n", htonl(INADDR_ANY));
    return 0;
}