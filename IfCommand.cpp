
#include "IfCommand.h"

// Perform the if command.
int IfCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    index++;
    int openingParenthesis = 0;
    while (strings[index] == "(") {
        index++;
        openingParenthesis++;
    }
    index = checkCondition(strings, index, dataBase, openingParenthesis);
    int startOfCommands = getStartIndexOfBlock();
    int open = 1;
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
    } else {
        index = ConditionParser::doCommand(strings, startOfCommands, dataBase);
        index++;
        if (index<strings.size()) {
            if (strings[index] == "\n" ) {
                index++;
            }
        }
    }
    return index;
}