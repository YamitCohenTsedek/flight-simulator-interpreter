
#include "Mult.h"

Mult::Mult(Expression* left, Expression* right) : BinaryExpression(left, right) {
    this->leftExpression = left;
    this->rightExpression = right;
}

// Calculate the value of the expression by applying the * operator on the left & right expressions.
double Mult:: calculate() {
    double result = this->leftExpression->calculate() * this->rightExpression->calculate();
    return result;
}

Mult:: ~Mult() {
}