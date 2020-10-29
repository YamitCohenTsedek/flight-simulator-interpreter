
#include "DefineVarCommand.h"

int DefineVarCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string "var", promote it by 1.
    ++index;
    // The current index is on the name of the variable.
    string varName = strings[index];
    /* 
     * If it is a binding, it has its own command, so skip to index + 2.
     * For example: if we have: var x = bind "....", we can "skip" on the commands DefineVarCommand (var)
     * and AssignmentCommand (=), since binding is always done in the line of the variable definition.
     */
    if (strings[index + 2] == "bind") {
        return index + 2;
    }
    // Else - add the variable to the symbol table (and initialize it with 0).
    dataBase->addVarToSymbolTable(varName);
    // The index current index is on the name of the variable, promote it by 1.
    return ++index;
}