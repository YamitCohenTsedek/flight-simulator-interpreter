
#include "BindCommand.h"

// Perform the bind command.
int BindCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    /*
     * The current index is on the string "bind", thus the name of the variable is in index-2.
     * For example: var x = bind ...
     */
    string varName = strings[index - 2];
    string path = "";
    string varPath = "";
    string secondVarName = "";
    // The current index is on the string "bind", promote it by 1.
    ++index;
    // If the binding is directly to some path of the simulator:
    if (strings[index] == "\"") {
        // The index is on the string " (that appears before the path), promote it by 1.
        ++index;
        while (strings[index] != "\"") {
            path += strings[index];
            ++index;
        }
        // The index is on the string " (that appears after the path), promote it by 1.
        ++index;
        dataBase->addBindingToSimulator(varName, path);
    // Else - it is a binding of variables.
    } else {
        secondVarName = strings[index];
        // Find the variable that is bounded to the simulator.
        if (dataBase->isBoundedToSimulator(secondVarName)) {
            varPath = dataBase->getPath(secondVarName);
            dataBase->addBindingToSimulator(varName, varPath);
            ++index;  // Promote the index by 1.
        } else {
            throw "Error - the binding is invalid.";
        }
    }
    // The current index is on the string '\n', promote it by 1.
    return ++index;
}