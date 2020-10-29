
#include "ExpressionCommand.h"

double ExpressionCommand:: calculate(vector<string> strings, int index, DataBase* dataBase) {
    return this->command->doCommand(strings, index, dataBase);
}