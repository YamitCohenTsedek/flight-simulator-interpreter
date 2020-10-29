
#ifndef FLIGHT_SIMULATOR_INTERPRETER_NUMBER_H
#define FLIGHT_SIMULATOR_INTERPRETER_NUMBER_H

#include "Expression.h"

class Number:  public Expression {
    double value;

public:
    Number(double num);
    virtual void set(Expression* num);
    virtual double calculate();
    virtual ~Number();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_NUMBER_H
