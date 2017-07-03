#include "Server.h"
#include <iostream>
#define STDIN 0

typedef struct sockaddr_in s_map;

Server::~Server()
{
    //dtor
}

void Server::create()
{
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(addr.sin_zero), '\0', 8);

    int yes = 1;

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    printf("##################################################\n");
    printf("#                 SERWER TESTOWY                 #\n");
    printf("##################################################\n\n\n");
}

void Server::bind_s()
{
    if (bind(sock_fd, getAddr(), sizeof(sockaddr)) == -1)
    {
        perror("bind");
    }

    printf("Serwer uruchomiony na porcie: %d\n", port);
}

void Server::listen_s(int m = 10)
{
    maxWaitingConnection = m;

    if (listen(sock_fd, maxWaitingConnection) == -1)
    {
        perror("listen");
    }

    printf("Nasluchiwanie uruchomione\n");

}

void Server::run()
{
    FD_SET(sock_fd, &master);
    fd_max = sock_fd;

   for(;;)
   {

        read_fds = master;

        if(select(fd_max+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }

        for(int i = 0; i <= fd_max; i++)
        {
            if (FD_ISSET(i,&read_fds))
            {
                if (i == sock_fd)
                {
                    socklen_t addlen = sizeof(their_addr);

                    if ((new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &addlen)) == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(new_fd, &master);
                        if (new_fd > fd_max)
                        {
                            fd_max = new_fd;
                        }
                        printf("New connection from: %s on socket: %d\n", inet_ntoa(their_addr.sin_addr), new_fd);
                        sock_map.insert(std::pair<int, s_map>(new_fd, their_addr));

                        for (auto kv : sock_map)
                        {
                            printf("socket: %d, ip: %s\n", kv.first, inet_ntoa(kv.second.sin_addr) );
                        }
                    }
                }
                else
                {
                    if ((nbytes = recv(i, buf,sizeof(buf),0)) <= 0)
                    {
                        if (nbytes == 0)
                        {
                            printf("Polaczone zerwane na sokecie: %d\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }

                        close(i);
                        FD_CLR(i, &master);
                    }
                    else
                    {
                        for (int j = 0; j <= fd_max; j++)
                        {
                            if (FD_ISSET(j, &master))
                            {
                                if (j!= sock_fd && j!= i)
                                {
                                    if (send(j, buf, nbytes,0) == -1)
                                    {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

   }


}

