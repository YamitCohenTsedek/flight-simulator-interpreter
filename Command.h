
#ifndef FLIGHT_SIMULATOR_INTERPRETER_COMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_COMMAND_H

#include <string.h>
#include <vector>
#include <iostream>
#include "ShuntingYard.h"
#include "DataBase.h"
#include "FindTwoParameters.h"

using namespace std;

/**
 * Command design pattern: define an interface named Command with doCommand() method, and for each command in the
 * system create a class from the Command type. Thus a polymorphic command can be a specific command, and all the
 * commands run in the same way. For our needs doCommand can get as an parameter an list of strings to interpret.
 */
class Command {
protected:
    ShuntingYard shuntingYard = ShuntingYard();
public:
    virtual int doCommand(vector<string> strings, int index, DataBase* dataBase) = 0;
    virtual ~Command(){}
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_COMMAND_H
