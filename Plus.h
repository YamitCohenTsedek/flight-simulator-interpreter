
#ifndef FLIGHT_SIMULATOR_INTERPRETER_PLUS_H
#define FLIGHT_SIMULATOR_INTERPRETER_PLUS_H

#include "BinaryExpression.h"

// Class Plus represents a binary expression with the + operator. 
class Plus : virtual public BinaryExpression {
    Expression* leftExpression;
    Expression* rightExpression;

public:
    Plus(Expression* left,Expression* right);

    // Calculate the value of the expression by applying the + operator on the left & right expressions.
    virtual double calculate();

    virtual ~Plus();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_PLUS_H
