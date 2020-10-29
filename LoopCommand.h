
#ifndef FLIGHT_SIMULATOR_INTERPRETER_LOOPCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_LOOPCOMMAND_H

#include "ConditionParser.h"
#include <vector>
using namespace std;

class LoopCommand : public ConditionParser {
public:
	// Perform the loop command.
	int doCommand(vector<string> strings, int indexes, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_LOOPCOMMAND_H
