
#ifndef FLIGHT_SIMULATOR_INTERPRETER_DIV_H
#define FLIGHT_SIMULATOR_INTERPRETER_DIV_H
#include <stdexcept>
#include "Number.h"
#include "BinaryExpression.h"

// Class Div represents a binary expression with the / operator. 
class Div : virtual public BinaryExpression {
    Expression* leftExpression;
    Expression* rightExpression;

public:
    Div(Expression* left,Expression* right);

	// Calculate the value of the expression by applying the / operator on the left & right expressions.
    virtual double calculate();

    virtual ~Div();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_DIV_H
