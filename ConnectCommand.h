
#ifndef FLIGHT_SIMULATOR_INTERPRETER_CONNECTCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_CONNECTCOMMAND_H

#include "Command.h"
#include <vector>
#include <string.h>
#include "DataWriterClient.h"
using namespace std;

class ConnectCommand : public Command {
public:
    // Perform the connect command.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_CONNECTCOMMAND_H