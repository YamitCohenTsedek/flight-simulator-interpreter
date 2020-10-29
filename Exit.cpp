
#include "Exit.h"
#include <unistd.h>

// Before exiting the program, close the sockets.
void Exit::closeSockets(DataBase* dataBase) {
    int serverSockedId = dataBase->getServerSockedId();
    close(serverSockedId);
    int clientSockedId = dataBase->getClientSockedId();
    close(clientSockedId);
}

// Before exiting the program, close the thread.
void Exit::closeThread(DataBase* dataBase) {
    dataBase->stopThread();
}

// Perform the Exit Command.
int Exit::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    closeSockets(dataBase);
    closeThread(dataBase);
    // The current index is on the string "exit", promote it by 1.
    return ++index;
}