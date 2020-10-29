
#include "ShuntingYard.h"

// Set the expression for the Shunting Yard algorithm.
void ShuntingYard::set(vector<string> newStr) {
    if (newStr.empty()) {
        throw std::runtime_error("ERROR: no strings were received to build an Expression from them.");
    }
    vector<string> expression;
    string finalExpression;
    expression = this->fixStrForPlusAndMinus(newStr);
    finalExpression = this->fixStringForNegative(expression);
    this->doExpre = finalExpression;
    this->all;
}

// Find the precedence of the operators.
int ShuntingYard::precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// Perform arithmetic operations.
Expression* ShuntingYard::applyOp(Expression* a, Expression* b, char op) {
    double value;
    switch (op) {
        case '+':
            value = (Plus(a, b)).calculate();
            break;
        case '-':
            value = (Minus(a, b).calculate());
            break;
        case '*':
            value = (Mult(a, b).calculate());
            break;
        case '/':
            value = (Div(a, b).calculate());
            break;
    }
    Expression* exNum = push(value);
    return exNum;
}

// Return the value obtained from the evaluation of the expression.
Expression* ShuntingYard::getEvaluation() {
    int i;
    string tokens = this->doExpre;
    // A stack to store integer values.
    stack <Expression*> values;
    // A stack to store operators.
    stack <char> ops;
    for (i = 0; i < tokens.length(); i++) {
        // If the current token is a whitespace - skip it.
        if (tokens[i] == ' ') {
            continue;
        }
        // Else - if the current token is an opening parenthesis, push it to 'ops'.
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }
        // Else - if the current token is a number, push it to stack of the numbers.
        else if (isdigit(tokens[i])) {
            string g = "";
            Number* val = push(0);
            Number* valDecimal = push(10);
            Number* result = push(0);
            Number* resultFinal = push(0);
            // There may be more than one digit in a number.
            while (i < tokens.length() && isdigit(tokens[i])) {
                g += tokens[i];
                val->set(applyOp(applyOp(val, valDecimal, '*') ,push(tokens[i] - '0'), '+'));
                i++;
            }
            if ((i < tokens.length()) && (tokens[i] == '.')) {
                i++;
                g += tokens[i];
                while (i < tokens.length() && isdigit(tokens[i])) {
                    result->set(applyOp(push((tokens[i] - '0')), valDecimal, '/'));
                    resultFinal->set(applyOp(result, resultFinal, '+'));
                    valDecimal->set(applyOp(valDecimal, push(10), '*'));
                    i++;
                }
            }
            values.push(applyOp(val, resultFinal, '+'));
            i -= 1;
        }
        // When encountering closing parenthesis, solve the entire expression.
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                Expression* val2 = values.top();
                values.pop();
                Expression* val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            // Pop the opening parenthesis - '('.
            ops.pop();
        }
        // Else - the current token is an operator.
        else {
            /*
             * While the top of 'ops' has the same or greater precedence than the current token, which is an operator,
             * apply the top operator of 'ops' on the top two elements of the values stack.
             */
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                Expression* val2 = values.top();
                values.pop();
                Expression* val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            // Push the current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // The entire expression has been parsed at this point, apply the remaining ops on the remaining values.
    while (!ops.empty()) {
        Expression* val2 = values.top();
        values.pop();
        Expression* val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    // The top of 'values' contains the result - return it.
    return values.top();}

/**
 * Simplify expressions that contain combinations of '+' and '-'.
 * @param st a vector of the strings of the expression.
 * @return the simplified expression.
 */
vector<string> ShuntingYard::fixStrForPlusAndMinus(vector<string> st) {
    vector<string> newString;
    for (int i = 1; i < st.size(); i++) {
        if ((st[i - 1] == st[i]) && (st[i] == "-")) {
            // The '#' should be changed and deleted.
            st[i - 1] = "#";
            st[i] = "+";
        }
        if ((st[i - 1] == st[i]) && (st[i] == "+")) {
            st[i - 1] = "#";
            st[i] = "+";
        }
        if (((st[i - 1] == "+") && (st[i] == "-")) || ((st[i - 1] == "+") && (st[i] == "-"))) {
            st[i - 1] = "#";
            st[i]= "-";
        }
    }
    for (int i = 0; i < st.size(); ++i){
        if (st[i] != "#") {
            string g = st[i];
            newString.push_back(g);
        }
    }
    return newString;
}

/**
 * Simplify expressions that contain negtive numbers.
 * @param st a vector of the strings of the expression.
 * @return the simplified expression.
 */
string ShuntingYard::fixStringForNegative(vector<string> st){
    string newString = "";
    bool flagClose = false;
    bool flag = false;
    if ((!st[0].compare("-") || (!st[0].compare("+")))) {
        newString += "(0";
        flag = true;
    }
    newString += st[0];
    for (int i = 1; i < st.size(); ++i) {
        if ((!st[i].compare("-") || ((!st[i].compare("+")))) && (!isdigit(st[i - 1][0]))) {
            if (st[i - 1] != ")") {
                newString += "(0";
                flagClose = true;
            }
        }
        if (!flag) {
            newString += st[i];
        }
        else {
            flag = false;
            if (!st[i].compare("(")) {
                newString += "1)*";
                newString += st[i];
            }
            else {
                newString += st[i];
                newString += ")";
            }
        }
        // Initialize the flag of the closing parenthesis for the next time.
        if (flagClose) {
            flag = true;
            flagClose = false;
        }
    }
    return newString;
}

Number* ShuntingYard::push(double num){
    Number* numer = new Number(num);
    all.push_back(numer);
    return numer;
}

ShuntingYard::~ShuntingYard() {
    for(int i = 0; i < all.size(); ++i) {
        delete (all[i]);
    }
}