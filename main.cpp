#include <iostream>
#include "Server.h"
#include "ServerManager.h"


using namespace std;

int main()
{

  auto serverManager = new ServerManager();
  serverManager->build();
  serverManager->run();

  delete serverManager;

  return 0;
}
