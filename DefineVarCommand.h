
#ifndef FLIGHT_SIMULATOR_INTERPRETER_DEFINEVARCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_DEFINEVARCOMMAND_H
#include "Command.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;

class DefineVarCommand : public Command {
public:
	// Perform the command of defining a variable.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_DEFINEVARCOMMAND_H
