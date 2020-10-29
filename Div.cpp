
#include "Div.h"

Div::Div(Expression* left, Expression* right) : BinaryExpression(left, right) {
    this->leftExpression = left;
    this->rightExpression = right;
}

// Calculate the value of the expression by applying the / operator on the left & right expressions.
double Div::calculate() {
    // In a case that the right expression is 0, throw a runtime error.
    if ((this->rightExpression)->calculate() == Number(0).calculate()) {
        throw std::runtime_error("ERROR: division by zero.");
    }
    double resulte = this->leftExpression->calculate() / this->rightExpression->calculate();
    return resulte;
}

Div:: ~Div(){
}