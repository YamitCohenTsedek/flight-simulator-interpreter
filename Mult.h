
#ifndef FLIGHT_SIMULATOR_INTERPRETER_MULT_H
#define FLIGHT_SIMULATOR_INTERPRETER_MULT_H

#include "BinaryExpression.h"

// Class Mult represents a binary expression with the * operator. 
class Mult : virtual public BinaryExpression {
    Expression* leftExpression;
    Expression* rightExpression;

public:
    Mult(Expression* left,Expression* right);

	// Calculate the value of the expression by applying the * operator on the left & right expressions.
    virtual double calculate();

    virtual ~Mult();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_MULT_H

