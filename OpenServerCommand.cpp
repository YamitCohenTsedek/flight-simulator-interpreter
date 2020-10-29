
#include "OpenServerCommand.h"
using namespace std;

// Perform the command of opening a server.
int OpenServerCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string "openDataServer", promote it by 1.
    ++index;
    vector<string> stringParams;
    while (strings[index] != "\n") {
        // If it is a variable, find its value and convert it to string.
        if (dataBase->isInSymbolTable(strings[index])) {
            string varValue = to_string(dataBase->getVarValue(strings[index]));
            stringParams.push_back(varValue);
            ++index;
            continue;
        }
        stringParams.push_back(strings[index]);
        ++index;
    }
    vector<vector<string>> twoParams = FindTwoParameters().find(stringParams, dataBase);
    // The first parameter (the port) is at index 0 and the second parameter (hz) is at index 1.
    vector<string> portStr = twoParams[0];
    // Calculate the expression by Shunting Yard algorithm.
    shuntingYard.set(portStr);
    double port = shuntingYard.getEvaluation()->calculate();
    int sockfd, newsockfd, portno, clilen;
    char buffer[BYTES_TO_READ];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;
    string str;
    // Open a socket to the server side.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // In case of an error while opening the socket, print an error message to stderr and exit.
    if (sockfd < 0) {
        perror("Error on opening the socket.");
        exit(1);
    }
    // Initialize socket structure.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    /*
     * Now bind the host address using bind() call.
     * In case of an error in the binding, print an error message to stderr and exit.
     */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding.");
        exit(1);
    }
    /*
     * Now start listening for clients. At this point the process will get into sleep mode
     * and will wait for the incoming connection.
     */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // Accept actual connection from a client.
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    dataBase->saveServerSockedId(newsockfd);
    // In case of an error in accepting the client, print an error message to stderr and exit.
    if (newsockfd < 0) {
        perror("Error on accepting the client.");
        exit(1);
    }
    struct Parameters *parameters = new Parameters();
    parameters->dataBase = dataBase;
    pthread_t id;
    pthread_create(&id, nullptr, DataReaderServer::createSocket, parameters);
    // The current index is on the string '\n', promote it by 1.
    return ++index;
};
