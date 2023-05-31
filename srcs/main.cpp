#include "../include/IRC.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        ErrorHandle::errorHandle("Usage : ./ircserv [port] [password]", 0);
    (void)argc;
    std::strstream sstream;
    int port;

    // port 번호 확인 65535 까지인지 확인,
    sstream << argv[1];
    sstream >> port;
    if (sstream.fail())
        ErrorHandle::errorHandle("port error", -1);

    IrcServ serv(port, argv[2]);
    serv.run();
/*
    printf("port : %d\n", port);
    printf("ip : %d\n", htonl(INADDR_ANY));
*/
    return 0;
}