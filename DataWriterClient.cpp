
#include "DataWriterClient.h"

// Create a client socket for connecting to the simulator and write data to it.
void DataWriterClient::createSocket(string host, int port, DataBase* dataBase) {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BYTES_TO_WRITE];
    portno = port;
    // Create a client socket.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // In case of an error on opening the socket, print an error message to stderr and exit.
    if (sockfd < 0) {
        perror("Error on opening the socket.");
        exit(1);
    }
    dataBase->saveClientSockedId(sockfd);
    server = gethostbyname(host.c_str());
    // In the given host is not exist, print an error message to stderr and exit.
    if (server == NULL) {
        fprintf(stderr,"Error: no such host.\n");
        exit(1);
    }
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    // Connect to the simulator. In case of an error on the connecting, print an error message to stderr and exit.
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on the connecting.");
        exit(1);
    }
}