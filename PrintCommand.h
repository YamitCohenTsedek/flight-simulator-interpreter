
#ifndef FLIGHT_SIMULATOR_INTERPRETER_PRINT_H
#define FLIGHT_SIMULATOR_INTERPRETER_PRINT_H
#include <string.h>
#include <vector>
#include "Command.h"

class PrintCommand : public Command {
public:
    // Perform the print command. Print Command prints the required string or the value of an expression.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_PRINT_H
