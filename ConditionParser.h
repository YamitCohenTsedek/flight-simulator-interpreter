
#ifndef FLIGHT_SIMULATOR_INTERPRETER_CONDITIONPASRSER_H
#define FLIGHT_SIMULATOR_INTERPRETER_CONDITIONPASRSER_H

#include "Command.h"
#include <vector>

using namespace std;

class ConditionParser : public Command {
private:
    int initialIndex;
    bool condition;
    vector <string> stringsOfCondition;
    // Evaluate the condition and return the result.
    bool evaluateCondition(vector<string> leftExp, vector<string> rightExp, string booleanOperator);

public:
    // Perform the condition parser command.
    int doCommand(vector<string> strings, int indexes, DataBase* dataBase);

    // Check what is the condition and evaluate it.
    int checkCondition(vector<string> strings, int index, DataBase* dataBase,int openCircle);

    bool isConditionTrue() {
        return condition;
    }

    int getStartIndexOfBlock() {
        return initialIndex;
    }
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_CONDITIONPASRSER_H
