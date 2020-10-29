
#ifndef FLIGHT_SIMULATOR_INTERPRETER_OPENSERVERCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_OPENSERVERCOMMAND_H
#include "Command.h"
#include <vector>
#include <string.h>
#include <iostream>
#include "DataReaderServer.h"
using namespace std;

class OpenServerCommand : public Command {
private:
    // Perform the command of opening a server.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);

public:
    struct Parameters {
        DataBase* dataBase;
    };
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_OPENSERVERCOMMAND_H
