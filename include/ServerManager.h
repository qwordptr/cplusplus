#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "Server.h"
#include <iostream>
#include <string>

class ServerManager
{
    public:
        void build();
        void run();
        ~ServerManager() {delete server ;}
        void showMessage(std::string m);

    protected:

    private:
      Server* server;
      int maxBufferSize = 255;
};

#endif // SERVERMANAGER_H
/*
for(i = 0; i <= fdmax; i++) {
    if (FD_ISSET(i, &read_fds)) { // mamy jednego!!
        if (i == listener) {
            // obsłu˙z nowe poł ˛aczenie
            addrlen = sizeof(remoteaddr);
            if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) == -1) {
                perror("accept");
            } else {
                FD_SET(newfd, &master); // dodaj do głównego zestawu
                if (newfd > fdmax) { // ´sled´z maksymalny
                fdmax = newfd;
                }
                printf("selectserver: new connection from %s on "
                "socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd);
            }
        } else {
            // obsłu˙z dane od klienta
            if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                // bł ˛ad lub poł ˛aczenie zostało zerwane
                if (nbytes == 0) {
                // poł ˛aczenie zerwera
                printf("selectserver: socket %d hung up\n", i);
                } else {
                perror("recv");
                }
                close(i); // papa!
                FD_CLR(i, &master); // usu´n z głównego zestawu
            } else {
                // mamy troch˛e danych od klienta
                for(j = 0; j <= fdmax; j++) {
                // wy´slij do wszystkich!
                    if (FD_ISSET(j, &master)) {
                        // oprócz nas i gniazda nasłuchuj ˛acego
                        if (j != listener && j != i) {
                            if (send(j, buf, nbytes, 0) == -1) {
                                perror("send");
                                }
                        }
                    }
                }
            }
        } // jakie to BRZYDKIE!!
    }
    }
}
*/
