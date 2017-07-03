#include "ServerManager.h"

using namespace std;

void ServerManager::build()
{
    cout <<"#################################################################" <<endl;
    cout <<"#                                                               #" <<endl;
    cout <<"#                     MANAGER SERWERA                           #" <<endl;
    cout <<"#                                                               #" <<endl;
    cout <<"#################################################################" <<endl;

    server = new Server(3399, 255);
    server->clearSocketSet();
    server->createSocket();
    server->bindSocket();
    server->startListen(10);
}

void ServerManager::run()
{
    for(;;)
    {
        server->startSelect();

        int newSock;


        for (int i = 0; i <= server->fdMax; i++)
        {
            if (i == server->sockFd)
            {
                if ((newSock = server->startAccept(i)) == -1) {
                    showMessage("Connection failed");
                } else if (newSock > 0) {
                    showMessage("New connection");
                }
            }
            else
            {
                server->recive(i);
            }
        }

    }
}

void ServerManager::showMessage(string message)
{
    cout << "Server response: " << message <<endl;
}
