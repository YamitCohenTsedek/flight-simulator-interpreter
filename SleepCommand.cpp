
#include "SleepCommand.h"

// Perform the sleep command.
int SleepCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string "sleep", promote it by 1.
    ++index;
    // Sleep command has only one argument, find it.
    string stringExpression = "";
    // Run over all the strings in the line.
    while (strings[index] != "\n") {
        if (dataBase->isInSymbolTable(strings[index]) || dataBase->isBoundedToSimulator(strings[index])) {
            strings[index] = dataBase->getVarValue(strings[index]);
        }
        stringExpression = stringExpression + strings[index];
        ++index;
    }
    Lexer lexer = Lexer();
    vector<string> splitedScript = lexer.spiltInfoToStrings(stringExpression);
    splitedScript.pop_back();
    // Calculate the value of the expression by Shunting Yard algorithm.
    shuntingYard.set(splitedScript);
    double result = shuntingYard.getEvaluation()->calculate();
    // usleep gets micro seconds, hence multiply the result by microseconds per second.
    usleep(result * MICROSECONS_PER_MILISECOND);
    // The current index is on '\n', promote it by 1.
    return ++index;
}