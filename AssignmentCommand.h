
#ifndef FLIGHT_SIMULATOR_INTERPRETER_ASSIGNMNET_H
#define FLIGHT_SIMULATOR_INTERPRETER_ASSIGNMNET_H
#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "Lexer.h"

/**
 * The Assignment Command is in charge of performing the assignments.
 * An assignment may be a binding of a variable to a path of the simulator,
 * or a regular assignment of a value in a variable from the symbol table.
 */
class AssignmentCommand : public Command {
private:
    // Send a message to the simulator through a socket to set its values.
    void sendMesseage(int sockfd, double value, string path);

    // Calculate the value that should be assigned to the variable.
    double calculateDouble(vector<string>& strings, int& index, DataBase* dataBase);

public:
    // Perform the assignment command.
    int doCommand(vector<string> strings, int indexes, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_ASSIGNMNET_H
