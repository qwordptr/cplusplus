#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <iostream>

class Server
{
    public:
        Server(int p, int b) : port(p), buffSize(b){};
        void createSocket();
        void clearSocketSet();
        void bindSocket();
        void startListen(int n);
        void startSelect();
        int startAccept(int i);
        char recive(int i);
        int fdMax;
        int sockFd;


    protected:

    private:

        int port;
        int maxWaitingConnection;
        int buffSize;
        sockaddr_in addr;
        fd_set master;
        fd_set readFds;

        sockaddr* pAddrCasted() { return ( struct sockaddr *)&addr ;}

};

#endif // SERVER_H



