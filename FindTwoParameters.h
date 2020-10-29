
#ifndef FLIGHT_SIMULATOR_INTERPRETER_FINDTWOPARAMETERS_H
#define FLIGHT_SIMULATOR_INTERPRETER_FINDTWOPARAMETERS_H
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "DataBase.h"
using namespace std;

class FindTwoParameters {
public:
	// Find two parameters of a binary expression.
    vector<vector<string>> find(vector<string> stringsOfParams, DataBase* dataBase);
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_FINDTWOPARAMETERS_H
