
#ifndef FLIGHT_SIMULATOR_INTERPRETER_DATAREADERSERVER_H
#define FLIGHT_SIMULATOR_INTERPRETER_DATAREADERSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include "DataBase.h"
#define BYTES_TO_READ 1024
#define NUM_OF_PATHS 35
using namespace std;

// Class DataReaderServer is in charge of creating a server that will read data from the simulator (the client).
class DataReaderServer {
public:
    struct Parameters {
        DataBase* dataBase;
    };

	// Open the server socket and wait for the simulator to connect. When it connects, read the data it sends.
	static void* createSocket(void* arg);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_DATAREADERSERVER_H
