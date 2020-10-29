
#include "LoopCommand.h"

// Perform the loop command.
int LoopCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    index++;
    int openingParenthesis = 0;
    while (strings[index] == "(") {
        index++;
        openingParenthesis++;
    }
    int indexCheck = index;
    index = checkCondition(strings, index, dataBase, openingParenthesis);
    int startOfCommands;
    int open = 1;
    int index2;
    bool flag = false;

    while (isConditionTrue()) {
        flag = true;
        startOfCommands = getStartIndexOfBlock();
        index2 = ConditionParser::doCommand(strings, startOfCommands, dataBase);
        index = checkCondition(strings, indexCheck, dataBase, openingParenthesis);
    }
    // In order not to do again.
    if (flag) {
        index = index2;
    }
    if (isConditionTrue() == false) {
        do {
            if (strings[index] == "{") {
                open++;
            }
            if (strings[index] == "}") {
                open--;
            }
            index++;
        }
        while (open != 0);
        index++;
    }
    return index;
}