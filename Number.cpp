
#include "Number.h"

Number::Number(double num) {
    this->value=num;
}

double Number::calculate() {
    return this->value;
}

void Number::set(Expression* num) {
    this->value=num->calculate();
}

Number::~Number(){
}