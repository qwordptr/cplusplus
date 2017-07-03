#include "Server.h"

void Server::createSocket()
{
    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    memset(&addr.sin_zero, '\0', 8);
}

void Server::bindSocket()
{
    int yes;

    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (bind(sockFd, pAddrCasted(), sizeof(sockaddr) ) == -1)
    {
        perror("bind");
        exit(1);
    }
}

void Server::startListen(int n)
{
    maxWaitingConnection = n;

    if (listen(sockFd, maxWaitingConnection) == -1)
    {
        perror("listen");
        exit(1);
    }

    FD_SET(sockFd, &master);
    fdMax = sockFd;
}

void Server::clearSocketSet()
{
    FD_ZERO(&master);
    FD_ZERO(&readFds);
}

void Server::startSelect()
{
    readFds = master;

    if(select(fdMax+1, &readFds, NULL, NULL, NULL) == -1)
    {
        perror("select");
    }
}

int Server::startAccept(int i)
{
        int newFd;
        sockaddr_in newAddr;
        socklen_t addrel = sizeof(newAddr);

        if (FD_ISSET(i, &readFds))
            {
                if ((newFd = accept(sockFd, (struct sockaddr *)&newAddr, &addrel)) == -1) {
                    perror("accept");
                    return -1;
                } else {
                    FD_SET(newFd, &master);
                    if (newFd > fdMax)  {
                        fdMax = newFd;
                    }

                    return newFd;
                }
            }


}

char Server::recive(int i)
{
    int bytes;
    char buffer[buffSize];

    if (FD_ISSET(i,&readFds))
    {
      if ((bytes = recv(i,buffer, sizeof(buffer),0 )) <= 0) {

      } else {
          std::cout << buffer;
          memset(buffer, '\0', sizeof(buffer));
      }
    }

}
