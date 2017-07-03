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


class Server
{
    public:
        Server(int p) : port(p){};
        void create();
        void bind_s();
        void listen_s(int m);
        void run();
        virtual ~Server();

    protected:

    private:
      struct sockaddr * getAddr() {return (struct sockaddr *)&addr;}
      int port;
      int maxWaitingConnection;
      int listener;
      int sock_fd;
      sockaddr_in addr;
      sockaddr_in remote;

      fd_set master;
      fd_set read_fds;
      int fd_max;
      int new_fd;

      sockaddr_in their_addr;
      char buf[256];
      socklen_t addrlen;
      int nbytes;

      std::map<int, sockaddr_in>sock_map;

};

#endif // SERVER_H



