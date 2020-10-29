
#include "FindTwoParameters.h"

// Find two parameters of a binary expression.
vector<vector<string>> FindTwoParameters::find(vector<string> strings, DataBase* dataBase) {
    vector<string> operators;
    operators.push_back("+");
    operators.push_back("-");
    operators.push_back("/");
    operators.push_back("*");
    operators.push_back(")");
    operators.push_back("(");
    int index = 0;
    bool isFirstParam = true;
    vector<string> firstParam;
    vector<string> secondParam;
    vector<vector<string>> twoParams;
    // Find the first parameter.
    bool isCurrentOperator;
    bool isNextOperator;
    while (isFirstParam) {
        isCurrentOperator = std::find(operators.begin(), operators.end(), strings[index]) != operators.end();
        if (index + 1 < strings.size()) {
            isNextOperator = std::find(operators.begin(), operators.end(), strings[index + 1]) != operators.end();
        }
        if (!isCurrentOperator && strings[index + 1] == "(") {
            isFirstParam = false;
        } else if (strings[index] == ")" && !isNextOperator) {
            isFirstParam = false;
        } else if (!isCurrentOperator && !isNextOperator) {
            isFirstParam = false;
        } else if (strings[index] == ")" && strings[index + 1] == "(") {
            isFirstParam = false;
        }
        if (dataBase->isInSymbolTable(strings[index])) {
            string varValue = to_string(dataBase->getVarValue(strings[index]));
            strings[index] = varValue;
        }
        firstParam.push_back(strings[index]);
        ++index;
    }
    // If the current character is a comma, it followed by the second parameter, and it's a negative number.
    if (strings[index] == ",") {
        ++index;
    }
    // Find the second parameter.
    for (int i = index; i < strings.size(); i++) {
        if (dataBase->isInSymbolTable(strings[index])) {
            string varValue = to_string(dataBase->getVarValue(strings[index]));
            strings[index] = varValue;
        }
        secondParam.push_back(strings[i]);
    }
    twoParams.push_back(firstParam);
    twoParams.push_back(secondParam);
    return twoParams;
}
