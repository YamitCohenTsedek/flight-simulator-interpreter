
#ifndef FLIGHT_SIMULATOR_INTERPRETER_EXITCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_EXITCOMMAND_H

#include "Command.h"

class Exit: public Command {
private:
    void closeSockets(DataBase* dataBase);
    void closeThread(DataBase* dataBase);

public:
	// Perform the Exit Command.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_EXITCOMMAND_H
