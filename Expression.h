
#ifndef FLIGHT_SIMULATOR_INTERPRETER_EXPRESSION_H
#define FLIGHT_SIMULATOR_INTERPRETER_EXPRESSION_H

class Expression {

public:
	// Calculate the value of the expression.
    virtual double calculate() = 0;
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_EXPRESSION_H