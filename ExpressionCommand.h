
#ifndef FLIGHT_SIMULATOR_INTERPRETER_EXPRESSIONCOMMAND_H
#define FLIGHT_SIMULATOR_INTERPRETER_EXPRESSIONCOMMAND_H

#include "Expression.h"
#include "Command.h"

class ExpressionCommand: public Expression {
    Command* command;

public:
    ExpressionCommand(Command* commandExpression) {
        this->command = commandExpression;
    }

    double calculate(vector<string> strings, int index, DataBase* dataBase);

    double calculate() {
    }
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_EXPRESSIONCOMMAND_H
