
#ifndef FLIGHT_SIMULATOR_INTERPRETER_IFCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    // Perform the if command.
    int doCommand(vector<string> strings, int indexes, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_IFCOMMAND_H