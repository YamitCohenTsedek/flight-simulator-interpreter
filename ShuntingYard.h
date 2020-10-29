
#ifndef FLIGHT_SIMULATOR_INTERPRETER_SHUNTINGYARD_H
#define FLIGHT_SIMULATOR_INTERPRETER_SHUNTINGYARD_H

#include <iostream>
#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>
#include <cstring>
#include <stack>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "Number.h"
#include "Plus.h"
#include "Minus.h"
#include "Mult.h"
#include "Div.h"

using namespace std;

class ShuntingYard {
    std::string doExpre;
    // The dynamically allocated expressions that their memory should be freed at the end.
    vector<Expression*> all;
    virtual Number* push(double num);

public:
    // Set the expression for the Shunting Yard algorithm.
    virtual void set(vector<string> st);

    // Return the value obtained from the evaluation of the expression.
    Expression* getEvaluation();

    // Perform arithmetic operations.
    Expression* applyOp(Expression* a, Expression* b, char op);

    // Find the precedence of the operators.
    int precedence(char op);

    /**
     * Simplify expressions that contain combinations of '+' and '-'.
     * @param st a vector of the strings of the expression.
     * @return the simplified expression.
     */
    virtual vector<string> fixStrForPlusAndMinus(vector<string> st);
    
    /**
     * Simplify expressions that contain negtive numbers.
     * @param st a vector of the strings of the expression.
     * @return the simplified expression.
     */
    virtual string fixStringForNegative(vector<string> st);

    virtual ~ShuntingYard();
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_SHUNTINGYARD_H
