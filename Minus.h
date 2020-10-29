
#ifndef FLIGHT_SIMULATOR_INTERPRETER_MINUS_H
#define FLIGHT_SIMULATOR_INTERPRETER_MINUS_H

#include "BinaryExpression.h"

// Class Minus represents a binary expression with the - operator. 
class Minus : public BinaryExpression {
    Expression* leftExpression;
    Expression* rightExpression;

public:
    Minus(Expression* left,Expression* right);

	// Calculate the value of the expression by applying the - operator on the left & right expressions.
    virtual double calculate();

    virtual ~Minus();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_MINUS_H
