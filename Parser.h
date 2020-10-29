
#ifndef FLIGHT_SIMULATOR_INTERPRETER_PARSER_H
#define FLIGHT_SIMULATOR_INTERPRETER_PARSER_H

#include <string.h>
#include "DataBase.h"
#include "ExpressionCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignmentCommand.h"
#include "BindCommand.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "Exit.h"

class Parser {
private:
    map<string, ExpressionCommand> stringToCommand;
    vector<Command*> commands;

public:
    Parser();

    // Interpret the commands and their arguments and execute them.
    int interpretScript(vector<string> strings, DataBase* dataBase);

    ~Parser();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_PARSER_H
