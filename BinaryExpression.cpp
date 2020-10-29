
#include "BinaryExpression.h"

// A binary expression is an expression that has a left expression and a right expression.
BinaryExpression::BinaryExpression(Expression* left, Expression* right) {
    this->leftExpression = left;
    this->rightExpression = right;
}

 BinaryExpression::~BinaryExpression() {
}