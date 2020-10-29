
#ifndef FLIGHT_SIMULATOR_INTERPRETER_BINARYEXPRESSION_H
#define FLIGHT_SIMULATOR_INTERPRETER_BINARYEXPRESSION_H
#include "Expression.h"

// A binary expression is an expression that has a left expression and a right expression.
class BinaryExpression:  public Expression {
protected:
    Expression* leftExpression;
    Expression* rightExpression;

public:
    BinaryExpression(Expression* left, Expression* right);
    virtual double calculate()=0;
    virtual ~BinaryExpression();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_BINARYEXPRESSION_H