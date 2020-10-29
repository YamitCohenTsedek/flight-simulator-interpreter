
#include "Parser.h"
using namespace std;

// Map between strings that represent commands and pointers to Command objects.
Parser::Parser() {

    // OpenServerCommand
    commands.push_back((Command*)new OpenServerCommand());
    ExpressionCommand openServer = ExpressionCommand(commands[0]);
    stringToCommand.insert(pair<string, ExpressionCommand>("openDataServer", openServer));

    // ConnectCommand
    commands.push_back((Command*)new ConnectCommand());
    ExpressionCommand connectCommand = ExpressionCommand(commands[1]);
    stringToCommand.insert(pair<string, ExpressionCommand>("connect", connectCommand));

    // DefineVarCommand
    commands.push_back((Command*)new DefineVarCommand());
    ExpressionCommand varCommand = ExpressionCommand(commands[2]);
    stringToCommand.insert(pair<string, ExpressionCommand>("var", varCommand));

    // AssignmentCommand
    commands.push_back((Command*)new AssignmentCommand());
    ExpressionCommand assignmentCommand = ExpressionCommand(commands[3]);
    stringToCommand.insert(pair<string, ExpressionCommand>("=", assignmentCommand));

    // BindCommand
    commands.push_back((Command*)new BindCommand());
    ExpressionCommand bindCommand = ExpressionCommand(commands[4]);
    stringToCommand.insert(pair<string, ExpressionCommand>("bind", bindCommand));

    // IfCommand
    commands.push_back((Command*)new IfCommand());
    ExpressionCommand ifCommand = ExpressionCommand(commands[5]);
    stringToCommand.insert(pair<string, ExpressionCommand>("if", ifCommand));

    // LoopCommand
    commands.push_back((Command*)new LoopCommand());
    ExpressionCommand loopCommand = ExpressionCommand(commands[6]);
    stringToCommand.insert(pair<string, ExpressionCommand>("while", loopCommand));

    // PrintCommand
    commands.push_back((Command*)new PrintCommand());
    ExpressionCommand printCommand = ExpressionCommand(commands[7]);
    stringToCommand.insert(pair<string, ExpressionCommand>("print", printCommand));

    // SleepCommand
    commands.push_back((Command*)new SleepCommand());
    ExpressionCommand sleepCommand = ExpressionCommand(commands[8]);
    stringToCommand.insert(pair<string, ExpressionCommand>("sleep", sleepCommand));
}


// Interpret the commands and their arguments and execute them.
int Parser::interpretScript(vector<string> strings, DataBase* dataBase) {
    int index = 0;
    while (index < strings.size()) {
        while (strings[index] == "\n") {
            ++index;
        }
        /*
         * If a variable appears at the beginning of a line, it means that it is an assignment
         * of a variable that was declared before, for example: x = 5 .In that case, reach to the string '='.
         */
        if (dataBase->isInSymbolTable(strings[index]) ||
            dataBase->isBoundedToSimulator(strings[index])) {
            ++index;
        }
        // Find the command that the index points to it in stringToCommand map.
        if (stringToCommand.find(strings[index]) != stringToCommand.end()) {
            ExpressionCommand command = stringToCommand.at(strings[index]);
            index = command.calculate(strings, index, dataBase);
        // Else - it is invalid command, throw an error.
        } else {
            throw std::invalid_argument("ERROR: The command is invalid.");
        }
    }
    return index;
}

Parser::~Parser() {
    for (vector<Command *>::iterator it = commands.begin();
         it != commands.end(); ++it) {
        delete (*it);
    }
}