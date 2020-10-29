
#ifndef FLIGHT_SIMULATOR_INTERPRETER_DATAWRITERCLIENT_H
#define FLIGHT_SIMULATOR_INTERPRETER_DATAWRITERCLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "DataBase.h"

#define BYTES_TO_WRITE 1024

using namespace std;

class DataWriterClient {
public:
    // Create a client socket for connecting to the simulator and write data to it.
    void createSocket(string host, int port, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_DATAWRITERCLIENT_H
