
#ifndef FLIGHT_SIMULATOR_INTERPRETER_LEXER_H
#define FLIGHT_SIMULATOR_INTERPRETER_LEXER_H

#include <string.h>
#include <vector>
#include <fstream>
#include "iostream"

using namespace std;

class Lexer {
public:
    // Split the string that contains the whole script into strings that should be interpreted. 
    vector<string> spiltInfoToStrings(string info);

    // Read the script from the specified file.
    vector<string> readFromFile(string fileName);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_LEXER_H
