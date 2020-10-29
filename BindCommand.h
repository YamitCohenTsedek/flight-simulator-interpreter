
#ifndef FLIGHT_SIMULATOR_INTERPRETER_BINDCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_BINDCOMMAND_H

#include <string.h>
#include <iostream>
#include "Command.h"

class BindCommand : public Command {
public:
    // Perform the bind command.
    int doCommand(vector<string> strings, int indexes, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_BINDCOMMAND_H