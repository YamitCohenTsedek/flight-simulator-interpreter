
#include "DataReaderServer.h"
#include <thread>
using namespace std;

// Open the server socket and wait for the simulator to connect. When it connects, read the data it sends.
void* DataReaderServer::createSocket(void* arg) {
    struct Parameters* parameters = (struct Parameters*)arg;
    char buffer[BYTES_TO_READ];
    int n;
    string buff;
    string leftStrings;
    // As long as the thread of the server is open - read from the socket.
    while (parameters->dataBase->isThreadShouldStop() == false) {
        // When the connection is established, start communicating.
        bzero(buffer, BYTES_TO_READ);
        int clientSockfd = parameters->dataBase->getClientSockedId();
        int serverSocketId = parameters->dataBase->getServerSockedId();
        n = read(serverSocketId, buffer, BYTES_TO_READ - 1);
        // In case of an error in reading from the socket, print an error message to stderr and exit.
        if (n < 0) {
            perror("ERROR reading from socket.");
            exit(1);
        }
        // Read the data from the socket.
        int position = 0;
        vector<string> data;
        string comma = ",";
        string enter = "\n";
        buff += buffer;
        position = buff.find(enter);
        leftStrings += buff.substr((0, position));
        leftStrings = leftStrings.substr(1);
        while ((position = buff.find(comma)) !=string::npos) {
            data.push_back(buff.substr(0,position));
            buff.erase(0, position + comma.length());
        }
        data.push_back(buff.substr(0, position));
        buff = "";
        for (int i = 0; i < NUM_OF_PATHS; ++i) {
            parameters->dataBase->updateSimulatorValue(i, stod(data[i]));
        }
        buff += leftStrings;
        leftStrings = "";
    }
}