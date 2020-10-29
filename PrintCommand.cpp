
#include "PrintCommand.h"
#include "DataBase.h"
#include "Lexer.h"
#include <iostream>

// Perform the print command. Print Command prints the required string or the value of an expression.
int PrintCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string "print", promote it by 1.
    ++index;
    string stringToPrint = "";
    vector <string> expression;
    string onlyString = "";
    // If it is a regular printing of a string, a quotation mark appears at the start.
    if (strings[index] == "\"" ) {
        // The current index is on the string ", promote it by 1.
        ++index;
        // Run to the end of the string.
        while (strings[index] != "\"") {
            stringToPrint += strings[index];
            ++index;
        }
        // The current index is on the string, promote it by 1.
        ++index;
        // A regular printing of a string.
        cout << stringToPrint << endl;
    // Else - it is a printing of a variable or an expression.
    } else {
        while (strings[index] != "\n") {
            // Check whether the expression includes variables and find their values.
            if ((dataBase->isInSymbolTable(strings[index]))) {
                string varValue = to_string(dataBase->getVarValue(strings[index]));
                strings[index] = varValue;
            }
            if (dataBase->isBoundedToSimulator(strings[index])) {
                string varValue = to_string(dataBase->getValueOfSimulatorShort(strings[index]));
                strings[index] = varValue;
            }
            onlyString = onlyString + strings[index];
            ++index;
        }
        // Find the evaluation of the expression, using Shunting Yard algorithm.
        Lexer lexer = Lexer();
        vector<string> splitedScript = lexer.spiltInfoToStrings(onlyString);
        splitedScript.pop_back();
        shuntingYard.set(splitedScript);
        cout << shuntingYard.getEvaluation()->calculate() << endl;
    }
    // The current index is on the string '\n' , promote it by 1.
    return ++index;
}