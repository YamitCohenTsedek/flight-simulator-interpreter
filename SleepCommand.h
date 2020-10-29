
#ifndef FLIGHT_SIMULATOR_INTERPRETER_SLEEP_H
#define FLIGHT_SIMULATOR_INTERPRETER_SLEEP_H
#include <unistd.h>
#include "Command.h"
#include "Lexer.h"
#define MICROSECONS_PER_MILISECOND 1000
using namespace std;

class SleepCommand : public Command {
public:
	// Perform the sleep command.
    int doCommand(vector<string> strings, int index, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_SLEEP_H
