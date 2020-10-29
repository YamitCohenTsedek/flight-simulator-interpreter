
#include "ConditionParser.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "ExpressionCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignmentCommand.h"
#include "BindCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "Parser.h"
#include "Lexer.h"

// Check what is the condition and evaluate it.
int ConditionParser::checkCondition(vector<string> strings, int index, DataBase* dataBase, int openingParenthesis) {
    // The index is on the string "(",promote it
    //++index;
    string leftExp="", rightExp="";
    string booleanOperator = "";
    string varValue = "";
    // Check where is the position of the boolean operator and stop on that position.
    while (strings[index] != "\n") {
        // If it is a (start of a) boolean operator:
        if (strings[index] == "<" || strings[index] == ">" || strings[index] == "=" || strings[index] == "!") {
            booleanOperator = strings[index];
            ++index;
            break;
        }
        if (dataBase->isInSymbolTable(strings[index])) {
            varValue = to_string(dataBase->getVarValue(strings[index]));
            strings[index] = varValue;
        }
        if(dataBase->isBoundedToSimulator(strings[index])) {
            string varValue = to_string(dataBase->getValueOfSimulatorShort(strings[index]));
            strings.at(index) = varValue;
        }
        leftExp = leftExp + strings[index];
        ++index;
    }
    // If it is an operator of 2 characters (for example: <=), the second character can be only '='.
    if (strings[index] == "=") {
        booleanOperator += strings[index];
        ++index;
    }
    // Find the elements of the right expression.
    while (((strings[index] != ")")) && (strings[index] != "{") && (strings[index] != "\n")) {
        if (dataBase->isInSymbolTable(strings[index])) {
            varValue = to_string(dataBase->getVarValue(strings[index]));
            strings[index] = varValue;
        }
        if (dataBase->isBoundedToSimulator(strings[index])) {
            string varValue = to_string(dataBase->getValueOfSimulatorShort(strings[index]));
            strings.at(index) = varValue;
        }
        rightExp = rightExp + strings[index];
        ++index;
    }
    if (strings[index] == ")") {
        openingParenthesis--;
        ++index;
    }
    while (openingParenthesis > 0) {
        if (strings[index] == ")") {
            openingParenthesis--;
        }
        index++;
    }
    /*
     * If the current index is on '{' (i.e. it appears in the line of the condition),
     * the following char should be the string '\n', thus promote the index by 1.
     */
    if (strings[index] == "{") {
        index = index + 2;
    /*
     * Else - the '{' appears on the following line, so the current index is on '\n' and then
     * should be '{' followed by '\n', thus promote the index by 3.
     */
    } else {
        if (strings[index - 1] == ")" && strings[index] == "\n") {
            index = index + 3;
        }
        if (strings[index] == "\n") {
            index++;
            if (strings[index] == "{") {
                index = index + 2;
            }
        }
    }
    // Use a lexer to split the left & right expressions to strings.
    Lexer lexer = Lexer();
    vector<string> leftExpVec = lexer.spiltInfoToStrings(leftExp);
    vector<string> rightExpVec = lexer.spiltInfoToStrings(rightExp);
    leftExpVec.pop_back();
    rightExpVec.pop_back();
    // Evaluate the condition and save the result.
    condition = evaluateCondition(leftExpVec, rightExpVec, booleanOperator);
    // Save and return the index of the first operation of the block.
    initialIndex = index;
    return index;
}

// Evaluate the condition and return the result.
bool ConditionParser::evaluateCondition(vector<string> leftExp, vector<string> rightExp, string booleanOperator) {
    shuntingYard.set(leftExp);
    double leftExpValue = shuntingYard.getEvaluation()->calculate();
    shuntingYard.set(rightExp);
    double rightExpValue = shuntingYard.getEvaluation()->calculate();
    if (booleanOperator == "<") {
        return (leftExpValue < rightExpValue);
    } else if (booleanOperator == "<=") {
        return (leftExpValue <= rightExpValue);
    } else if (booleanOperator == ">") {
        return (leftExpValue > rightExpValue);
    } else if (booleanOperator == ">=") {
        return (leftExpValue >= rightExpValue);
    } else if (booleanOperator == "==") {
        return (leftExpValue == rightExpValue);
    } else if (booleanOperator == "!=") {
        return (leftExpValue != rightExpValue);
    } else {
        throw "ERROR: The operator is invalid.";
    }
}

// Perform the condition parser command.
int ConditionParser::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    stringsOfCondition = {};
    int open = 1;
    for (int i = initialIndex; i < strings.size(); i++ ) {
        if (strings[i] == "}") {
            open--;
            if (open == 0) {
                break;
            }
        }
        if (strings[i] == "{") {
            open++;
        }
        stringsOfCondition.push_back(strings[i]);
    }
    Parser parser = Parser();
    int endOfBlock = parser.interpretScript(stringsOfCondition, dataBase);
    return index + endOfBlock;
}